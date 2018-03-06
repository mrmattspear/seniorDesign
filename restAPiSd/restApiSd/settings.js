const express = require('express');
settingsRouter = express.Router
module.exports = settingsRouter;

settingsRouter.get('/new', config, function (req, res, next) {    //HTTP GET 
    mssqlRequest.requestData(config);
});

settingsRouter.delete('/new', config, function (req, res, next) { //HTTP DELETE
    mssql.deleteData(config);
});

settingsRouter.put('/new', config, function (req, res, next) {    //HTTP PUT
    mssql.updateData(config);
});

settingsRouter.post('/new', config, function (req, res, next) {   //HTTP POST
    mssqlRequest.sendData(config);
});