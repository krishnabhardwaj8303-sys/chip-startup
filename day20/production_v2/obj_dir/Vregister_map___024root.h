// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vregister_map.h for the primary calling header

#ifndef VERILATED_VREGISTER_MAP___024ROOT_H_
#define VERILATED_VREGISTER_MAP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class Vregister_map__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vregister_map___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(reg_write,0,0);
    VL_IN8(reg_read,0,0);
    VL_IN8(reg_addr,7,0);
    VL_OUT8(reg_ready,0,0);
    VL_IN8(bist_pass_i,0,0);
    VL_IN8(bist_fail_i,0,0);
    VL_IN8(wdt_timeout_i,0,0);
    VL_IN8(glitch_detected_i,0,0);
    VL_IN8(aes_done_i,0,0);
    VL_OUT8(aes_start_o,0,0);
    VL_OUT8(bist_start_o,0,0);
    VL_OUT8(wdt_enable_o,0,0);
    CData/*0:0*/ register_map__DOT____Vtogcov__clk;
    CData/*0:0*/ register_map__DOT____Vtogcov__rst;
    CData/*0:0*/ register_map__DOT____Vtogcov__reg_write;
    CData/*0:0*/ register_map__DOT____Vtogcov__reg_read;
    CData/*7:0*/ register_map__DOT____Vtogcov__reg_addr;
    CData/*0:0*/ register_map__DOT____Vtogcov__reg_ready;
    CData/*0:0*/ register_map__DOT____Vtogcov__bist_pass_i;
    CData/*0:0*/ register_map__DOT____Vtogcov__bist_fail_i;
    CData/*0:0*/ register_map__DOT____Vtogcov__wdt_timeout_i;
    CData/*0:0*/ register_map__DOT____Vtogcov__glitch_detected_i;
    CData/*0:0*/ register_map__DOT____Vtogcov__aes_done_i;
    CData/*0:0*/ register_map__DOT____Vtogcov__aes_start_o;
    CData/*0:0*/ register_map__DOT____Vtogcov__bist_start_o;
    CData/*0:0*/ register_map__DOT____Vtogcov__wdt_enable_o;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(reg_wdata,31,0);
    VL_OUT(reg_rdata,31,0);
    VL_INW(aes_result_i,127,0,4);
    VL_OUTW(aes_key_o,127,0,4);
    VL_OUTW(aes_plaintext_o,127,0,4);
    IData/*31:0*/ register_map__DOT____Vtogcov__reg_wdata;
    IData/*31:0*/ register_map__DOT____Vtogcov__reg_rdata;
    VlWide<4>/*127:0*/ register_map__DOT____Vtogcov__aes_result_i;
    VlWide<4>/*127:0*/ register_map__DOT____Vtogcov__aes_key_o;
    VlWide<4>/*127:0*/ register_map__DOT____Vtogcov__aes_plaintext_o;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vregister_map__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vregister_map___024root(Vregister_map__Syms* symsp, const char* v__name);
    ~Vregister_map___024root();
    VL_UNCOPYABLE(Vregister_map___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
