// dispatch_fix.cpp -- tolerate calls to null/invalid/unregistered guest functions.
//
// v0.8.0's rex::runtime::ResolveIndirectFunction returns a trap that REX_FATALs
// when the guest calls an unregistered address (e.g. a null function pointer left
// by a failed file open). The old toolkit's PPC_CALL_INDIRECT_FUNC instead
// NULL-checked and skipped. This overrides the (exported) resolver to return a
// no-op trampoline for invalid targets, so the guest continues instead of aborting.
//
// Requires /force:multiple at link (we redefine an exported rexruntime symbol;
// project objects link first, so ours wins). See templates/STUBS.md.

#include <cstdio>

#include <rex/ppc/context.h>
#include <rex/runtime.h>
#include <rex/system/function_dispatcher.h>

namespace {

// No-op stand-in for an unresolved indirect call: log the first few, return 0.
void NoopTrap(PPCContext& ctx, uint8_t* /*base*/) {
  static int logged = 0;
  if (logged < 25) {
    std::FILE* f = std::fopen("dispatch_fix.log", "a");
    if (f) {
      std::fprintf(f, "tolerated indirect call to unregistered target 0x%08X\n",
                   (unsigned)ctx.last_indirect_target);
      std::fclose(f);
    }
    ++logged;
  }
  ctx.r3.u64 = 0;
}

}  // namespace

namespace rex::runtime {

// Overrides the SDK definition (exported; /force:multiple selects ours).
::PPCFunc* ResolveIndirectFunction(uint32_t guest_address) {
  if (Runtime* rt = Runtime::instance())
    if (FunctionDispatcher* d = rt->function_dispatcher())
      if (::PPCFunc* f = d->GetFunction(guest_address))
        return f;
  return &NoopTrap;
}

}  // namespace rex::runtime
