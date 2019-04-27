var express=require("express");
var app=express();
var bodyParser=require("body-parser");
var http=require('http');
var getJSON = require('get-json')

app.set("view engine","ejs");
app.use(bodyParser.urlencoded({extended:true}));

app.get("/",function(req,res){
	res.render("landing");
});

app.get("/login",function(req,res){
res.render("login");

});
var flag={
	space1:{
    position:"empty",
    booked:"false"
  },
	space2:{

    position:"empty",
    booked:"false"
  
  }
};

app.post("/login",function(req,res){
 var l_data=req.body;
 //pulkit data
 if((l_data.username==="pulkit")&&(l_data.password==="pulkit11@")){
 	res.render("./pulkit",{data:flag});
  console.log(flag);
 }
 if((l_data.username==="jignesh")&&(l_data.password==="jignesh123")){
    
    getJSON('https://smartparking-62de8.firebaseio.com/space.json', function(error, response){
 
    
    // undefined
 
    res.render('./jignesh',{space:response});
    // ["Beth Orton &mdash; Stolen Car",
    // "Jack White &mdash; Temporary Ground",
    // "I Am Kloot &mdash; Loch",
    // "Portishead &mdash; Glory Box"]
});
 	// res.render("./jignesh");
 }
 else{
 res.send("please enter valid details!!!");}

});

app.get("/jignesh",function(req,res){
	// var datto=req.body.username;
	// flag=datto;
	// res.send(flag);


  // var data = req.body;
  // res.send(data);
  // console.log(data);
  
res.render('/');

	
});

app.get("/pulkit",function(req,res){
	res.send(flag);
});

app.post("/overall",function(req,res){
var data=req.body;
var data1=data.space1;
var data2=data.space2;
console.log(data1,data2);
flag.space1.position=data1;
flag.space2.position=data2;
console.log(flag);
res.render("./landing");

});

app.listen(3000,function(req,res){
console.log("working!!");

});
