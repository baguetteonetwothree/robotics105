#ifndef __PROPELLER_BUILTINS_H__
#define __PROPELLER_BUILTINS_H__

#ifdef __cplusplus
extern "C"
{
#endif
  void __builtin_propeller_clkset(int mode);

  int __builtin_propeller_cogid();

  int __builtin_propeller_coginit(int id);

  void __builtin_propeller_cogstop(int a);

  void __builtin_propeller_locknew();
  
  void __builtin_propeller_lockret(int lockid);

  void __builtin_propeller_lockset(int lockid);

  void __builtin_propeller_lockclr(int lockid);

  int __builtin_propeller_waitcnt(int a, int b);

  void __builtin_propeller_waitpeq(int state, int mask);

  void __builtin_propeller_waitpne(int state, int mask);

  void __builtin_propeller_waitvid(long colors, int pixels);
  
#ifdef __cplusplus
}
#endif

#endif // __PROPELLER_BUILTINS_H__
