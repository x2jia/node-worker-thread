const fs = require('fs')
const path = require('path')
const assert = require('assert')
const Promise = require('bluebird')
const THREAD = require('../build/Release/workers.node').THREAD

const Thread =  function (filename) {
  const maintain = function() {
    return arguments.length
  }

  const o = {
    close() {
      thread_.close()
    },
    isRunning() {
      return thread_.isRunning()
    },
    numOfTasks() {
      return thread_.queNum()
    },
    Independent0(name, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      return thread_.Independent0(name, function(err, ret) {
        assert.equal(maintain(name), 1)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent1(name, p1, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      return thread_.Independent1(name, p1, function(err, ret) {
        assert.equal(maintain(name, p1), 2)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent2(name, p1, p2, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      return thread_.Independent2(name, p1, p2, function(err, ret) {
        assert.equal(maintain(name, p1, p2), 3)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent3(name, p1, p2, p3, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      return thread_.Independent3(name, p1, p2, p3, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3), 4)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent4(name, p1, p2, p3, p4, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      if(!Buffer.isBuffer(p4)) {
        p4 = new Buffer.from(p4)
      }
      return thread_.Independent4(name, p1, p2, p3, p4, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3, p4), 5)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent5(name, p1, p2, p3, p4, p5, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      if(!Buffer.isBuffer(p4)) {
        p4 = new Buffer.from(p4)
      }
      if(!Buffer.isBuffer(p5)) {
        p5 = new Buffer.from(p5)
      }
      return thread_.Independent5(name, p1, p2, p3, p4, p5, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3, p4, p5), 6)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent6(name, p1, p2, p3, p4, p5, p6, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      if(!Buffer.isBuffer(p4)) {
        p4 = new Buffer.from(p4)
      }
      if(!Buffer.isBuffer(p5)) {
        p5 = new Buffer.from(p5)
      }
      if(!Buffer.isBuffer(p6)) {
        p6 = new Buffer.from(p6)
      }
      return thread_.Independent6(name, p1, p2, p3, p4, p5, p6, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3, p4, p5, p6), 7)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent7(name, p1, p2, p3, p4, p5, p6, p7, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      if(!Buffer.isBuffer(p4)) {
        p4 = new Buffer.from(p4)
      }
      if(!Buffer.isBuffer(p5)) {
        p5 = new Buffer.from(p5)
      }
      if(!Buffer.isBuffer(p6)) {
        p6 = new Buffer.from(p6)
      }
      if(!Buffer.isBuffer(p7)) {
        p7 = new Buffer.from(p7)
      }
      return thread_.Independent7(name, p1, p2, p3, p4, p5, p6, p7, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3, p4, p5, p6, p7), 8)
        setImmediate(() => cb(err, ret))
      })
    },
    Independent8(name, p1, p2, p3, p4, p5, p6, p7, p8, cb) {
      if(!Buffer.isBuffer(name)) {
        name = new Buffer.from(name)
      }
      if(!Buffer.isBuffer(p1)) {
        p1 = new Buffer.from(p1)
      }
      if(!Buffer.isBuffer(p2)) {
        p2 = new Buffer.from(p2)
      }
      if(!Buffer.isBuffer(p3)) {
        p3 = new Buffer.from(p3)
      }
      if(!Buffer.isBuffer(p4)) {
        p4 = new Buffer.from(p4)
      }
      if(!Buffer.isBuffer(p5)) {
        p5 = new Buffer.from(p5)
      }
      if(!Buffer.isBuffer(p6)) {
        p6 = new Buffer.from(p6)
      }
      if(!Buffer.isBuffer(p7)) {
        p7 = new Buffer.from(p7)
      }
      if(!Buffer.isBuffer(p8)) {
        p8 = new Buffer.from(p8)
      }
      return thread_.Independent8(name, p1, p2, p3, p4, p5, p6, p7, p8, function(err, ret) {
        assert.equal(maintain(name, p1, p2, p3, p4, p5, p6, p7, p8), 9)
        setImmediate(() => cb(err, ret))
      })
    }
  }

  var codes
  if(filename) {
    codes = fs.readFileSync(filename)
  } else {
    codes = fs.readFileSync(path.join(__dirname, 'out', 'export.js'))
  }
  var thread_ =  new THREAD(codes)
  codes = null
  Promise.promisifyAll(o, {suffix: 'Async'})

  return {
    close() {
      o.close()
    },
    isRunning() {
      return o.isRunning()
    },
    numOfTasks() {
      return o.numOfTasks()
    },
    execute() {
      const length = arguments.length
      var last = arguments[length - 1]
      if(typeof last === 'function' && last.constructor.name === 'Function') {
        if(length === 2) {
          return o.Independent0.apply(o, arguments)
        } else if(length === 3) {
          return o.Independent1.apply(o, arguments)
        } else if(length === 4) {
          return o.Independent2.apply(o, arguments)
        } else if(length === 5) {
          return o.Independent3.apply(o, arguments)
        } else if(length === 6) {
          return o.Independent4.apply(o, arguments)
        } else if(length === 7) {
          return o.Independent5.apply(o, arguments)
        } else if(length === 8) {
          return o.Independent6.apply(o, arguments)
        } else if(length === 9) {
          return o.Independent7.apply(o, arguments)
        } else if(length === 10) {
          return o.Independent8.apply(o, arguments)
        } else {
          throw new Error('params len > 8')
        }
      } else {
        if(length === 1) {
          return o.Independent0Async.apply(o, arguments)
        } else if(length === 2) {
          return o.Independent1Async.apply(o, arguments)
        } else if(length === 3) {
          return o.Independent2Async.apply(o, arguments)
        } else if(length === 4) {
          return o.Independent3Async.apply(o, arguments)
        } else if(length === 5) {
          return o.Independent4Async.apply(o, arguments)
        } else if(length === 6) {
          return o.Independent5Async.apply(o, arguments)
        } else if(length === 7) {
          return o.Independent6Async.apply(o, arguments)
        } else if(length === 8) {
          return o.Independent7Async.apply(o, arguments)
        } else if(length === 9) {
          return o.Independent8Async.apply(o, arguments)
        } else {
          throw new Error('params len > 8')
        }
      }
    }
  }
}

module.exports = Thread
