const express = require('express'),
path = require('path')
const app = express()
const port = 3000

app.set('view engine', 'ejs');
app.set('views', path.resolve( __dirname, 'views'));


app.get('/tutorial', function (req, res) {
  res.render('tutorial', {})
})

app.get('/simplex', function(req, res) {
  res.render('simplex', {})
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
