#ifndef RCIB_VM_
#define RCIB_VM_

class VMRe : public rcib::Param {
public:
  explicit VMRe(base::WeakPtr<base::Thread> thr) {
    _data = nullptr;
    _thr = thr;
    if (thr.get()) thr->IncComputational();
  }

  virtual ~VMRe() {
    // to free mem
    if (_data) free(_data);
    // to dec num of tasks in this thr
    if (_thr.get()) _thr->DecComputational();
  }

  uint8_t * _data;
  base::WeakPtr<base::Thread> _thr;
};

class VmHelper {
public:
  class ParamWrapper2 {
  public:
    ParamWrapper2(int pNum);
    char *p1, *p2;
    int p1_len, p2_len;
    char *name;
    int name_len;
    int pNum;
  };

  class ParamWrapper4 {
  public:
    ParamWrapper4(int pNum);
    char *p1, *p2, *p3, *p4;
    int p1_len, p2_len, p3_len, p4_len;
    char * name;
    int name_len;
    int pNum;
  };

  class ParamWrapper8 {
  public:
    ParamWrapper8(int pNum);
    char *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;
    int p1_len, p2_len, p3_len, p4_len, p5_len, p6_len, p7_len, p8_len;
    char *name;
    int name_len;
    int pNum;
  };

  explicit VmHelper();

  static VmHelper* GetInstance();
  
  void Controller2(ParamWrapper2 params, rcib::async_req * req, base::Thread *thread);
  void Controller4(ParamWrapper4 params, rcib::async_req * req, base::Thread *thread);
  void Controller8(ParamWrapper8 params, rcib::async_req * req, base::Thread *thread);

private:
  void Init();
};

#endif
