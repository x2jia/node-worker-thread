const path = require('path')
const Thread = require('../index.js').Thread
const EQSTR = '{3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}'

// create a new thread
const thread = new Thread(path.join(__dirname, 'thread2.js'))

console.log('thread is', thread.isRunning() ? 'running' : 'stoped')

// run task in the thread
thread.execute('inc',
  'apple+', (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('two',
  EQSTR.substr(0, 1),
  EQSTR.substr(1), (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('three',
  EQSTR.substr(0, 1),
  EQSTR.substr(1, 1),
  EQSTR.substr(2), (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('four',
  EQSTR.substr(0, 1),
  EQSTR.substr(1, 1),
  EQSTR.substr(2, 1),
  EQSTR.substr(3), (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('five',
  EQSTR.substr(0, 1),
  EQSTR.substr(1, 1),
  EQSTR.substr(2, 1),
  EQSTR.substr(3, 1),
  EQSTR.substr(4), (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('six',
  EQSTR.substr(0, 1),
  EQSTR.substr(1, 1),
  EQSTR.substr(2, 1),
  EQSTR.substr(3, 1),
  EQSTR.substr(4, 1),
  EQSTR.substr(5), (err, data) => {
    console.log(err, data.toString())
  })

thread.execute('seven',
  EQSTR.substr(0, 1),
  EQSTR.substr(1, 1),
  EQSTR.substr(2, 1),
  EQSTR.substr(3, 1),
  EQSTR.substr(4, 1),
  EQSTR.substr(5, 1),
  EQSTR.substr(6), (err, data) => {
    console.log(err, data.toString())
})

thread.execute('eight',
              EQSTR.substr(0, 1),
              EQSTR.substr(1, 1),
              EQSTR.substr(2, 1),
              EQSTR.substr(3, 1),
              EQSTR.substr(4, 1),
              EQSTR.substr(5, 1),
              EQSTR.substr(6, 1),
              EQSTR.substr(7), (err, data) => {
                console.log(err, data.toString())
              })


console.log('thread task number is', thread.numOfTasks())
