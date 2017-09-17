var Particle = require('particle-api-js');
var express = require('express');
var particle = new Particle();
var token = "85a371f66f6e24f11e0fda996a09329b5f47eabd";
var app = express();
var bodyParser = require('body-parser');
var methodOverride = require('method-override');

app.use(bodyParser.urlencoded({
  extended: true
}))
app.use(bodyParser.json())
app.use(methodOverride())
app.use(express.static('public'))

app.get('/api/devices', function (req, res) {
  particle.listDevices({ auth: token })
  .then(function (devices) {
    res.json(devices.body);
  }, function (err) {
    console.log(err);
  });
});

app.post('/api/toppings', function (req, res) {
  particle.callFunction({
    deviceId: '27003f001747353236343033',
    name: 'pizza',
    argument: req.body.toppings,
    auth: token
  }).then(function(data) {
    console.log('it worked!');
    console.log(data);
    res.json(data);
  }, function (err) {
    console.log(err);
  })
});

app.post('/api/price', function (req, res) {
  particle.callFunction({
    deviceId: '27003f001747353236343033',
    name: 'pizzaPrice',
    argument: req.body.price,
    auth: token
  }).then(function(data) {
    console.log('it worked!');
    console.log(data);
    res.json(data);
  }, function (err) {
    console.log(err);
  })
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
})
