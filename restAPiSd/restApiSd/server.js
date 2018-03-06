// node.js modules
var express = require('express');                       //    -express: web framework 
var app = express();                                    //       +express object instance
var sql = require('mssql');                             //    -mssql: server client
var mssqlRequest = require('mssqlRequest');        
                                                            
// Middleware:
app.use(bodyParser.json());                             //    -JSON body parser


//Import Routers:
const powerRouter = require('power');                   //    -power  
const temperatureRouter = require('temperature');       //    -temperature
const errorsRouter = require('errors');                 //    -errors
const settingsRouter = require('settings');             //    -settings

//Mount Router:
app.use('power', config, powerRouter);                  //    -power
app.use('temperature', config, temperatureRouter);      //    -temperature
app.use('errors', config, errorsRouter);                //    -errors
app.use('settings', config, settingsRouter);            //    -settings

                        
// Connection string parameters:
var config = {
    user: 'DesignServer',
    password: 'seniordesign',
    server: 'DESKTOP-RU7BKJG',
    database: 'SENIOR_DESIGN',
}

//start server and listen
var server = app.listen( port, function () {
    var host = server.address().address
    var port = server.address().port

    console.log(`app listening at http://${host}:${port}`);
});
