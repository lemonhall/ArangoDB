/*jslint indent: 2, nomen: true, maxlen: 100, white: true  plusplus: true, browser: true*/
/*global describe, beforeEach, afterEach, it, spyOn, expect*/
/*global $*/

(function() {
  "use strict";

  describe("The new logs view", function() {

    var view, allLogs, debugLogs, infoLogs, warnLogs, errLogs, div;

    beforeEach(function() {
      div = document.createElement("div");
      div.id = "content";
      document.body.appendChild(div);
      allLogs = new window.NewArangoLogs(
        {upto: true, loglevel: 4}
      );
      debugLogs = new window.NewArangoLogs(
        {loglevel: 4}
      );
      infoLogs = new window.NewArangoLogs(
        {loglevel: 3}
      );
      warnLogs = new window.NewArangoLogs(
        {loglevel: 2}
      );
      errLogs = new window.NewArangoLogs(
        {loglevel: 1}
      );
      spyOn(allLogs, "fetch");
      view = new window.NewLogsView({
        logall: allLogs,
        logdebug: debugLogs,
        loginfo: infoLogs,
        logwarning: warnLogs,
        logerror: errLogs
      });
      expect(allLogs.fetch).toHaveBeenCalled();
      view.render();
    });

    afterEach(function() {
      document.body.removeChild(div);
    });

    it("assert basics", function () {
      expect(view.currentLoglevel).toEqual("logall");
      expect(view.id).toEqual("#logContent");
    });

    it("check set not same active log level function", function () {
      var button = {
        currentTarget: {
          id: "logdebug"
        }
      }
      spyOn(view, "convertModelToJSON");
      view.setActiveLoglevel(button);
      expect(view.convertModelToJSON).toHaveBeenCalled();
      expect(view.currentLoglevel).toBe(button.currentTarget.id);
    });

    it("check set same active log level function", function () {
      var button = {
        currentTarget: {
          id: "logall"
        }
      }
      spyOn(view, "convertModelToJSON");
      view.setActiveLoglevel(button);
      expect(view.convertModelToJSON).not.toHaveBeenCalled();
      expect(view.currentLoglevel).toBe(button.currentTarget.id);
    });

    it("set active log level to loginfo", function () {
      allLogs.fetch.reset();
      spyOn(infoLogs, "fetch");
      $("#loginfo").click();
      expect(infoLogs.fetch).toHaveBeenCalled();
      expect(allLogs.fetch).not.toHaveBeenCalled();
    });


  });


}());
