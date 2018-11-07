//we declare here a function so the app variable that runs our code is not a global variable
// but instead is a local variable to the function
(function() {

  //we declare here our app. This is called by index.html with the directive ng-app
  //<body ng-app="MY_APP" ng-controller="ParticleCtrl">
  var app = angular.module('MY_APP', ['ionic'])

  //we declare here our controller. This is run in the index.html by the directive ng-controller
  //<body ng-app="MY_APP" ng-controller="ParticleCtrl">
  app.controller('MyFirstAppCtrl', function($scope, $http) {

    //let's declare some variables
    $scope.temperature = "";
    $scope.responseStatus = "";
    $scope.responseDescription = "";

    //this is the declaration of the function that sends the http request to the Particle Cloud
    $scope.callFunctionOnTheParticleCloud = function() {
      $scope.responseStatus = "Calling a function on the Particle cloud";
      $scope.responseDescription = "";

      var requestVariable = {
        method: 'POST',
        url: 'https://api.particle.io/v1/devices/yourdeviceID/led?access_token=',
        data: {
          value: 'on'
        }
      }

      $http(requestVariable).then(function(response) {
        $scope.responseStatus = response.status;
        $scope.responseDescription = response.data;
      }, function(response) {
        $scope.responseStatus = response.data || "Request failed";
        $scope.responseDescription = response.status;
      });
    };

    //this is the declaration of the function that sends the http request to the Particle Cloud
    $scope.getVariableFromTheParticleCloud = function() {
      $scope.responseStatus = "Getting a variable from the Particle cloud";
      $scope.responseDescription = "";

      var getVariable = {
        method: 'GET',
        url: 'https://api.particle.io/v1/devices/yourdeviceID/led?access_token=',
        headers: {
          'Authorization': "Bearer 1234"
        },
        data: {
          test: 'test'
        }
      }

      $http(getVariable).then(function(response) {
        $scope.responseStatus = response.status;
        $scope.responseDescription = response.data;
        //this statement gets the temperature out of the result json field
        // example: "result":"{\"t\":27.69}"
        //source: http://stackoverflow.com/questions/7033334/how-to-extract-number-from-a-string-in-javascript
        $scope.temperature = parseInt(response.data.result.replace(/[^0-9\.]/g, ''), 10);

      }, function(response) {
        $scope.responseStatus = response.data || "Request failed";
        $scope.responseDescription = response.status;
      });

      //signal that the refresh is over
      $scope.$broadcast('scroll.refreshComplete');

    };

    $scope.callAnotherFunctionOnTheParticleCloud = function() {
      $scope.responseStatus = "Calling a function on the Particle cloud";
      $scope.responseDescription = "";

      var requestVariable = {
        method: 'POST',
        url: 'https://api.particle.io/v1/devices/yourdeviceID/led?access_token=',
        data: {
          value: 'off'
        }
      }

      $http(requestVariable).then(function(response) {
        $scope.responseStatus = response.status;
        $scope.responseDescription = response.data;
      }, function(response) {
        $scope.responseStatus = response.data || "Request failed";
        $scope.responseDescription = response.status;
      });
    };

  });

  app.run(function($ionicPlatform) {
    $ionicPlatform.ready(function() {
      if (window.cordova && window.cordova.plugins.Keyboard) {
        cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
        cordova.plugins.Keyboard.disableScroll(true);
      }
      if (window.StatusBar) {
        StatusBar.styleDefault();
      }
    });
  })
}());
