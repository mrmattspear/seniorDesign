const express = require('express');
errrorsRouter = express.Router();
module.exports = errorsRouter;

errorsRouter.get('/new', config, function (req, res, next) {    //HTTP GET 
    mssqlRequest.requestData(config);
});

errorsRouter.delete('/new', config, function (req, res, next) { //HTTP DELETE
    mssql.deleteData(config);
});

errorsRouter.put('/new', config, function (req, res, next) {    //HTTP PUT
    mssql.updateData(config);
});

errorsRouter.post('/new', config, function (req, res, next) {   //HTTP POST
    mssqlRequest.sendData(config);
});