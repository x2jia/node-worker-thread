```
-----------------------------✈--------------------------
   |-------------------------✈--------------------------
   |-------------------------✈--------------------------
   |-------------------------✈--------------------------
```

A framework let node support multi threads

### Node Version Required
node >= 14.0.0

### Dependencies
bluebird

### Getting Started

This section contains guides for understanding and mastering features that this module offers.

you can run the file of main.js in sample folder.

```
jia@youjia MINGW64 /c/worker-thread2/sample
$ node main.js
thread is running
thread task number is 8
null apple+apple+
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
null {3C3EE61D-1B2E-4167-AA04-90E8510AD3DA}
```

### Platform Support
> OS X, Windows and Linux

### Node engine
> \>=14.0.0

### Cpu architectures

Not support arm , mips

### Installation

**Unix**
```
  GCC 4.9.4 or newer
  Clang 3.4.2 or newer
  Python 2.6 or 2.7
```

**Windows**
```
  Building native add-ons: Visual Studio 2013 or Visual C++ Build Tools 2019 or newer
  Python 2.6 or 2.7
```

Once you have Node.js installed:

```
npm install -g node-gyp
npm install worker-thread2
```

**OS X**
```
xcodebuild
```

Having installation troubles? Check out [Supported toolchains](https://github.com/nodejs/node/blob/master/BUILDING.md#supported-toolchains)

### APIs

**close**
通知线程对象管理的线程退出，即从线程的消息循环中退出，结束线程的运行。线程对象以后不再使用，应该调用这个函数，及时的释放系统资源。如果没有调用这个函数，而线程对象满足 V8 垃圾回收的条件被回收的时候，会自动释放底层资源。因此，这个函数的调用不是必须的。但我们建议，由于线程是系统资源，如果确定不再使用，应该手动调用 close 及时释放底层资源。

**isRunning**
判断这个线程对象是否存在可用线程。线程对象创建成功后，内部的线程已经就绪，调用这个函数返回 true。close 函数调用之后，isRunning 返回 false。

**numOfTasks**
交给线程对象执行的任务队列中的个数。即排队中的，还没来得及执行的任务个数。程序中可以创建多个线程对象，可以用这个函数做负载均衡，将任务交给 numOfTasks 个数最小的线程对象。

**execute**
让线程对象执行一个函数，每个函数就是一个任务，线程对象内部有一个消息队列，抛给线程对象执行的任务以队列的方式按序执行。这样的函数，execute 支持向它传递 [0, 8] 个参数，参数类型为 Buffer，如果是字符串，则自动转为 Buffer。

### License
Apache-2.0

### 说明
我的这个解决方案是2017年做好的。比node原生模块worker_threads早。node 8, 10 的用户使用muti-thread，功能一样。个人感觉，这个实现方案用起来更简单，更好理解。

