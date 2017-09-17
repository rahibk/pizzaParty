var http = require('http');
var fs = require('fs');
var Particle = require('particle-api-js');
var pizzapi = require('pizzapi');
var particle = new Particle();
var token;

particle.login({username: 'muizchunara98@gmail.com', password: '98ztr4jg'}).then(
function(data) {
  token = data.body.access_token;
},
function (err) {
  console.log('Could not log in.', err);
}
);
var devicesPr = particle.listDevices({ auth: token });

devicesPr.then(
function(devices){
  console.log('Devices: ', devices);
},
function(err) {
  console.log('List devices call failed: ', err);
}
);

  pizzapi.Util.findNearbyStores(
      '200 University Ave, Waterloo, ON, N2L3G1',
      'Delivery',
      function(storeData){
          console.log(storeData);
      }
  );

const PORT=8000;
fs.readFile('./index.html', function (err, html) {

    //if (err) throw err;

    http.createServer(function(request, response) {
        response.writeHeader(200, {"Content-Type": "text/html"});
        response.write(html);
        response.end();
    }).listen(PORT);
});
