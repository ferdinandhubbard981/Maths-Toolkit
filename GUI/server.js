const express = require('express'),
path = require('path')
const bodyParser = require('body-parser');
const app = express();

const port = 3000

app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs');
app.set('views', path.resolve( __dirname, 'views'));


app.get('/tutorial', function (req, res) {
  res.render('tutorial', {})
})

app.post('/tutorial', function(req, res){
    console.log(req.body);
});

app.get('/simplex', function(req, res) {
  res.render('simplex', {})
})

app.get('/matrix', function(req, res) {
  res.render('matrix', {})
})

app.post('/matrix', function(req, res){
  test = req.body;
  console.log(test);
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
