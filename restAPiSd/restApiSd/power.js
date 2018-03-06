const express = require('express');
powerRouter = express.Router();
module.exports = powerRouter;


powerRouter.get('/power/new', config, function (req, res, next) {    //HTTP GET 
    mssqlRequest.requestData(config);
});

powerRouter.delete('/power/new', config, function (req, res, next) { //HTTP DELETE
    mssql.deleteData(config);
});

powerRouter.put('/power/new', config, function (req, res, next) {    //HTTP PUT
    mssql.updateData(config);
});

powerRouter.post('/power/new', config, function (req, res, next) {   //HTTP POST
    mssqlRequest.sendData(config);
});

