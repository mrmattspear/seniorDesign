module.exports.mssqlRequest = mssqlRequest;

mssqlRequest = {
    requestData = function (config) {

        var serverConnect = sql.connect(config);                           //create connect object
                                                                           
        serverConnect.connect()                                            
            .then(function () {                                            //connect
                                                                           
                var request = new sql.Request();                           // create Request object
                                                                           
                request.query('select * from new')                         
                    .then(function (err, recordset) {                      //query
                        res.send(recordset);                               //send records 
                        close();                                           //close connection
                    }).catch(function (err) {                              //query error catch
                        console.log(err);                                  //log error
                        close();                                           //close connection
                    });                                                    
            }).catch(function (err) {                                      //connection error catch
                console.log('connection error' + err);                     //log error
            });
    },

    deleteData = function (config) {

        var serverConnect = sql.connect(config);                           //create connect object

        serverConnect.connect()                                            //connect
            .then(function () {   

                var transaction = new sql.Transaction(config);             //create transaction object

                request.query('DELETE new')
                    .then(function () {                                    //query server
                        transaction.commit()                               
                            .then(function (recordset) {                   //transaction
                                console.log(recordset);                    //log transaction
                                close();                                   //close connection
                            }).catch(function (err) {                      // commit error catch
                                console.log('commit error' + err);         //log commit error
                                close();                                   //close connection 
                            });                                            
                    }).catch(function (err) {                              //query error catch
                        console.log('query error' + err);                  //log query error
                        close();                                           //close connection
                    });            
                transaction.begin()                                        //begin transaction
                    .then(function () {

                        var request = new sql.Request(transaction);        //create request object 

                    }).catch(function (err) {                              //begin error catch
                        console.log('begin error' + err);                  //log begin error
                        close();                                           //close connection
                    });    
            }).catch(function (err) {                                      //connection error catch
                console.log('connection error' + err);                     //log connection error
            });

    },

    updateData = function (config) {
        var serverConnect = sql.connect(config);                           //create connect object

        serverConnect.connect()                                            //connect
            .then(function () {

                var transaction = new sql.Transaction(config);             //create transaction object

                request.query('UPDATE new WHERE datumID = ' + datumID)
                    .then(function () {                                    //query server
                        transaction.commit()
                            .then(function (recordset) {                   //transaction
                                console.log(recordset);                    //log transaction
                                close();                                   //close connection
                            }).catch(function (err) {                      // commit error catch
                                console.log('commit error' + err);         //log commit error
                                close();                                   //close connection 
                            });
                    }).catch(function (err) {                              //query error catch
                        console.log('query error' + err);                  //log query error
                        close();                                           //close connection
                    });
                transaction.begin()                                        //begin transaction
                    .then(function () {

                        var request = new sql.Request(transaction);        //create request object 

                    }).catch(function (err) {                              //begin error catch
                        console.log('begin error' + err);                  //log begin error
                        close();                                           //close connection
                    });
            }).catch(function (err) {                                      //connection error catch
                console.log('connection error' + err);                     //log connection error
            });
    },


    sendData = function (config) {

        var serverConnect = sql.connect(config);                           //create connect object
                                                                           
        serverConnect.connect()                                            //connect
            .then(function () {                                            
                                                                           
                var transaction = new sql.Transaction(config);             //create transaction object
                                                                           
                transaction.begin()                                        //begin transaction
                    .then(function () {                                    
                                                                           
                        var request = new sql.Request(transaction);        //create request object

                        request.query('INSERT INTO new PowerDatum (powerLevel, timeStamp) values (power, time)')
                            .then(function () {                            //query server
                                transaction.commit()                       
                                    .then(function (recordset) {           //transaction
                                        console.log(recordset);            //log transaction
                                        close();                           //close connection
                                    }).catch(function (err) {              // commit error catch
                                        console.log('commit error' + err); //log commit error
                                        close();                           //close connection 
                                    });
                            }).catch(function (err) {                      //query error catch
                                console.log('query error' + err);          //log query error
                                close();                                   //close connection
                            });                                            
                    }).catch(function (err) {                              //begin error catch
                        console.log('begin error' + err);                  //log begin error
                        close();                                           //close connection
                    });                                                    
            }).catch(function (err) {                                      //connection error catch
                console.log('connection error' + err);                     //log connection error
            });
    }
};