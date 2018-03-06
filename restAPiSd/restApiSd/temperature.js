const express = require('express');

temperatureRouter = express.Router();

module.exports = temperatureRouter;

temperatureRouter.get('/new', config, function (req, res, next) {    //HTTP GET 
    mssqlRequest.requestData(config);
});
   
temperatureRouter.delete('/new', config, function (req, res, next) { //HTTP DELETE
    mssql.deleteData(config);
});

tmperatureRouter.put('/new', config, function (req, res, next) {     //HTTP PUT
    mssql.updateData(config);
});

temperatureRouter.post('/new', config, function (req, res, next) {   //HTTP POST
    mssqlRequest.sendData(config);
});