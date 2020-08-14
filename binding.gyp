{
  'targets': [
    {
      'target_name': 'workers',
      'defines': [ 'V8_DEPRECATION_WARNINGS=1' ],
      'sources': [
        'src/binding.cc',
        'src/node/rcib_object.cc',
        'src/node/globals.cc',
        'src/node/rcib_object.h',
        'src/node/rcib.h',
        'src/base/at_exist.cc',
        'src/base/lazy_instance.cc',
        'src/base/MessageLoop.cc',
        'src/base/MessagePumpDefault.cc',
        'src/base/PendingTask.cc',
        'src/base/ref_counted.cc',
        'src/base/Thread.cc',
        'src/base/Thread.h',
        'src/base/util_tools.cc',
        'src/base/WeakPtr.cc',
        'src/base/Event/WaitableEvent.cc',
        'src/base/time/time.cc',
        'src/base/roler.cc',
        'src/vm/vm.cc',
        'src/vm/vm.h'
      ],
      'win_delay_load_hook': 'false'
    }
  ]
}
