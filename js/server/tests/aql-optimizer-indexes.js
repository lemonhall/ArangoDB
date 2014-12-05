/*jshint strict: false, maxlen: 500 */
/*global require, assertTrue, assertEqual, assertNotEqual, AQL_EXPLAIN, AQL_EXECUTE */

////////////////////////////////////////////////////////////////////////////////
/// @brief tests for index usage
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2012 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

var jsunity = require("jsunity");
var db = require("org/arangodb").db;

////////////////////////////////////////////////////////////////////////////////
/// @brief test suite
////////////////////////////////////////////////////////////////////////////////

function optimizerIndexesTestSuite () {
  var c;

  return {
    setUp : function () {
      db._drop("UnitTestsCollection");
      c = db._create("UnitTestsCollection");

      for (var i = 0; i < 2000; ++i) {
        c.save({ _key: "test" + i, value: i });
      }

      c.ensureSkiplist("value");
    },

    tearDown : function () {
      db._drop("UnitTestsCollection");
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexSimple : function () {
      var query = "FOR i IN " + c.name() + " FILTER i.value >= 10 SORT i.value LIMIT 10 RETURN i.value";

      var plan = AQL_EXPLAIN(query).plan;
      var nodeTypes = plan.nodes.map(function(node) {
        return node.type;
      });

      assertEqual("SingletonNode", nodeTypes[0], query);
      assertNotEqual(-1, nodeTypes.indexOf("IndexRangeNode"), query);
      assertEqual(-1, nodeTypes.indexOf("SortNode"), query);
      assertEqual("ReturnNode", nodeTypes[nodeTypes.length - 1], query);

      var results = AQL_EXECUTE(query);
      assertEqual([ 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ], results.json, query);
      assertEqual(0, results.stats.scannedFull);
      assertTrue(results.stats.scannedIndex > 0);
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexJoin : function () {
      var query = "FOR i IN " + c.name() + " FILTER i.value == 8 FOR j IN " + c.name() + " FILTER i.value == j.value RETURN i.value";

      var plan = AQL_EXPLAIN(query).plan;
      var indexes = 0;
      plan.nodes.map(function(node) {
        if (node.type === "IndexRangeNode") {
          ++indexes;
        }
        return node.type;
      });
      assertEqual(2, indexes);

      var results = AQL_EXECUTE(query);
      assertEqual([ 8 ], results.json, query);
      assertEqual(0, results.stats.scannedFull);
      assertTrue(results.stats.scannedIndex > 0);
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexJoinJoin : function () {
      var query = "FOR i IN " + c.name() + " FILTER i.value == 8 FOR j IN " + c.name() + " FILTER i._key == j._key RETURN i.value";

      var plan = AQL_EXPLAIN(query).plan;
      var indexes = 0;
      plan.nodes.map(function(node) {
        if (node.type === "IndexRangeNode") {
          ++indexes;
        }
        return node.type;
      });
      assertEqual(2, indexes);

      var results = AQL_EXECUTE(query);
      assertEqual([ 8 ], results.json, query);
      assertEqual(0, results.stats.scannedFull);
      assertTrue(results.stats.scannedIndex > 0);
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexJoinJoinJoin : function () {
      var query = "FOR i IN " + c.name() + " FILTER i.value == 8 FOR j IN " + c.name() + " FILTER i.value == j.value FOR k IN " + c.name() + " FILTER j.value == k.value RETURN i.value";

      var plan = AQL_EXPLAIN(query).plan;
      var indexes = 0;
      plan.nodes.map(function(node) {
        if (node.type === "IndexRangeNode") {
          ++indexes;
        }
        return node.type;
      });
      assertEqual(3, indexes);

      var results = AQL_EXECUTE(query);
      assertEqual([ 8 ], results.json, query);
      assertEqual(0, results.stats.scannedFull);
      assertTrue(results.stats.scannedIndex > 0);
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexSubquery : function () {
      var query = "LET results = (FOR i IN " + c.name() + " FILTER i.value >= 10 SORT i.value LIMIT 10 RETURN i.value) RETURN results";

      var plan = AQL_EXPLAIN(query).plan;
      var nodeTypes = plan.nodes.map(function(node) {
        return node.type;
      });

      assertEqual("SingletonNode", nodeTypes[0], query);
      assertEqual("SubqueryNode", nodeTypes[1], query);

      var subNodeTypes = plan.nodes[1].subquery.nodes.map(function(node) {
        return node.type;
      });
      assertNotEqual(-1, subNodeTypes.indexOf("IndexRangeNode"), query);
      assertEqual(-1, subNodeTypes.indexOf("SortNode"), query);
      assertEqual("ReturnNode", nodeTypes[nodeTypes.length - 1], query);

      var results = AQL_EXECUTE(query);
      assertEqual([ 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ], results.json[0], query);
      assertEqual(0, results.stats.scannedFull);
      assertTrue(results.stats.scannedIndex > 0);
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testUseIndexSubSubquery : function () {
      var query = "FOR i IN " + c.name() + " LIMIT 1 RETURN (FOR j IN " + c.name() + " FILTER j._key == i._key RETURN j.value)";

      var plan = AQL_EXPLAIN(query).plan;
      var nodeTypes = plan.nodes.map(function(node) {
        return node.type;
      });

      assertEqual("SingletonNode", nodeTypes[0], query);
      var idx = nodeTypes.indexOf("SubqueryNode");
      assertNotEqual(-1, idx, query);

      var subNodeTypes = plan.nodes[idx].subquery.nodes.map(function(node) {
        return node.type;
      });
      assertNotEqual(-1, subNodeTypes.indexOf("IndexRangeNode"), query);
      assertEqual(-1, subNodeTypes.indexOf("SortNode"), query);
      assertEqual("ReturnNode", nodeTypes[nodeTypes.length - 1], query);

      var results = AQL_EXECUTE(query);
      assertTrue(results.stats.scannedFull > 0); // for the outer query
      assertTrue(results.stats.scannedIndex > 0); // for the inner query
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test index usage
////////////////////////////////////////////////////////////////////////////////

    testMultipleSubqueries : function () {
      var query = "LET a = (FOR x IN " + c.name() + " FILTER x._key == 'test1' RETURN x._key) " + 
                  "LET b = (FOR x IN " + c.name() + " FILTER x._key == 'test2' RETURN x._key) " + 
                  "LET c = (FOR x IN " + c.name() + " FILTER x._key == 'test3' RETURN x._key) " + 
                  "LET d = (FOR x IN " + c.name() + " FILTER x._key == 'test4' RETURN x._key) " + 
                  "LET e = (FOR x IN " + c.name() + " FILTER x._key == 'test5' RETURN x._key) " + 
                  "LET f = (FOR x IN " + c.name() + " FILTER x._key == 'test6' RETURN x._key) " + 
                  "LET g = (FOR x IN " + c.name() + " FILTER x._key == 'test7' RETURN x._key) " + 
                  "LET h = (FOR x IN " + c.name() + " FILTER x._key == 'test8' RETURN x._key) " + 
                  "LET i = (FOR x IN " + c.name() + " FILTER x._key == 'test9' RETURN x._key) " + 
                  "LET j = (FOR x IN " + c.name() + " FILTER x._key == 'test10' RETURN x._key) " +
                  "RETURN [ a, b, c, d, e, f, g, h, i, j ]";


      var explain = AQL_EXPLAIN(query);
      var plan = explain.plan;

      var walker = function (nodes, func) {
        nodes.forEach(function(node) {
          if (node.type === "SubqueryNode") {
            walker(node.subquery.nodes, func);
          }
          func(node);
        });
      };

      var indexNodes = 0, collectionNodes = 0;
      walker(plan.nodes, function (node) {
        if (node.type === "IndexRangeNode") {
          ++indexNodes;
        }
        else if (node.type === "EnumerateCollectionNode") {
          ++collectionNodes;
        }
      });

      assertEqual(0, collectionNodes);
      assertEqual(10, indexNodes);
      assertEqual(1, explain.stats.plansCreated);

      var results = AQL_EXECUTE(query);
      assertEqual(0, results.stats.scannedFull);
      assertNotEqual(0, results.stats.scannedIndex); 
      assertEqual([ [ [ 'test1' ], [ 'test2' ], [ 'test3' ], [ 'test4' ], [ 'test5' ], [ 'test6' ], [ 'test7' ], [ 'test8' ], [ 'test9' ], [ 'test10' ] ] ], results.json);
    }

  };
}

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the test suite
////////////////////////////////////////////////////////////////////////////////

jsunity.run(optimizerIndexesTestSuite);

return jsunity.done();

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// @addtogroup\\|// --SECTION--\\|/// @page\\|/// @}\\)"
// End: