var Particle = require('particle-api-js');
var express = require('express');
var particle = new Particle();
var token = "85c44d13873160a590360851d3eeb7e0a0981b11";
var app = express()

var bodyParser = require('body-parser')
var methodOverride = require('method-override')

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
    name: 'led',
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



app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
})
