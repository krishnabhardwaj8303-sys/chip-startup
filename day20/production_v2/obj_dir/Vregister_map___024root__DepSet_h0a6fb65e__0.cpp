// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vregister_map.h for the primary calling header

#include "Vregister_map__pch.h"
#include "Vregister_map__Syms.h"
#include "Vregister_map___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__ico(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG

void Vregister_map___024root___eval_triggers__ico(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vregister_map___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vregister_map___024root___ico_sequent__TOP__0(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.clk) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__clk))) {
        ++(vlSymsp->__Vcoverage[0]);
        vlSelfRef.register_map__DOT____Vtogcov__clk 
            = vlSelfRef.clk;
    }
    if (((IData)(vlSelfRef.rst) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__rst))) {
        ++(vlSymsp->__Vcoverage[1]);
        vlSelfRef.register_map__DOT____Vtogcov__rst 
            = vlSelfRef.rst;
    }
    if (((IData)(vlSelfRef.reg_write) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_write))) {
        ++(vlSymsp->__Vcoverage[2]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_write 
            = vlSelfRef.reg_write;
    }
    if (((IData)(vlSelfRef.reg_read) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_read))) {
        ++(vlSymsp->__Vcoverage[3]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_read 
            = vlSelfRef.reg_read;
    }
    if (((IData)(vlSelfRef.bist_pass_i) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__bist_pass_i))) {
        ++(vlSymsp->__Vcoverage[77]);
        vlSelfRef.register_map__DOT____Vtogcov__bist_pass_i 
            = vlSelfRef.bist_pass_i;
    }
    if (((IData)(vlSelfRef.bist_fail_i) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__bist_fail_i))) {
        ++(vlSymsp->__Vcoverage[78]);
        vlSelfRef.register_map__DOT____Vtogcov__bist_fail_i 
            = vlSelfRef.bist_fail_i;
    }
    if (((IData)(vlSelfRef.wdt_timeout_i) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__wdt_timeout_i))) {
        ++(vlSymsp->__Vcoverage[79]);
        vlSelfRef.register_map__DOT____Vtogcov__wdt_timeout_i 
            = vlSelfRef.wdt_timeout_i;
    }
    if (((IData)(vlSelfRef.glitch_detected_i) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__glitch_detected_i))) {
        ++(vlSymsp->__Vcoverage[80]);
        vlSelfRef.register_map__DOT____Vtogcov__glitch_detected_i 
            = vlSelfRef.glitch_detected_i;
    }
    if (((IData)(vlSelfRef.aes_done_i) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__aes_done_i))) {
        ++(vlSymsp->__Vcoverage[81]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_done_i 
            = vlSelfRef.aes_done_i;
    }
    if ((1U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[4]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xfeU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (1U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((2U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[5]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xfdU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (2U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((4U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[6]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xfbU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (4U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((8U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[7]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xf7U & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (8U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((0x10U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[8]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xefU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (0x10U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((0x20U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[9]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xdfU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (0x20U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((0x40U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[10]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0xbfU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (0x40U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((0x80U & ((IData)(vlSelfRef.reg_addr) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)))) {
        ++(vlSymsp->__Vcoverage[11]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_addr 
            = ((0x7fU & (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_addr)) 
               | (0x80U & (IData)(vlSelfRef.reg_addr)));
    }
    if ((1U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[12]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (1U & vlSelfRef.reg_wdata));
    }
    if ((2U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[13]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (2U & vlSelfRef.reg_wdata));
    }
    if ((4U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[14]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (4U & vlSelfRef.reg_wdata));
    }
    if ((8U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[15]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (8U & vlSelfRef.reg_wdata));
    }
    if ((0x10U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[16]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x10U & vlSelfRef.reg_wdata));
    }
    if ((0x20U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[17]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x20U & vlSelfRef.reg_wdata));
    }
    if ((0x40U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[18]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x40U & vlSelfRef.reg_wdata));
    }
    if ((0x80U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[19]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x80U & vlSelfRef.reg_wdata));
    }
    if ((0x100U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[20]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x100U & vlSelfRef.reg_wdata));
    }
    if ((0x200U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[21]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x200U & vlSelfRef.reg_wdata));
    }
    if ((0x400U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[22]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x400U & vlSelfRef.reg_wdata));
    }
    if ((0x800U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[23]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x800U & vlSelfRef.reg_wdata));
    }
    if ((0x1000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[24]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x1000U & vlSelfRef.reg_wdata));
    }
    if ((0x2000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[25]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x2000U & vlSelfRef.reg_wdata));
    }
    if ((0x4000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[26]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x4000U & vlSelfRef.reg_wdata));
    }
    if ((0x8000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[27]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x8000U & vlSelfRef.reg_wdata));
    }
    if ((0x10000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[28]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x10000U & vlSelfRef.reg_wdata));
    }
    if ((0x20000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[29]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x20000U & vlSelfRef.reg_wdata));
    }
    if ((0x40000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[30]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x40000U & vlSelfRef.reg_wdata));
    }
    if ((0x80000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[31]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x80000U & vlSelfRef.reg_wdata));
    }
    if ((0x100000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[32]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x100000U & vlSelfRef.reg_wdata));
    }
    if ((0x200000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[33]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x200000U & vlSelfRef.reg_wdata));
    }
    if ((0x400000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[34]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x400000U & vlSelfRef.reg_wdata));
    }
    if ((0x800000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[35]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x800000U & vlSelfRef.reg_wdata));
    }
    if ((0x1000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[36]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x1000000U & vlSelfRef.reg_wdata));
    }
    if ((0x2000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[37]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x2000000U & vlSelfRef.reg_wdata));
    }
    if ((0x4000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[38]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x4000000U & vlSelfRef.reg_wdata));
    }
    if ((0x8000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[39]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x8000000U & vlSelfRef.reg_wdata));
    }
    if ((0x10000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[40]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x10000000U & vlSelfRef.reg_wdata));
    }
    if ((0x20000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[41]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x20000000U & vlSelfRef.reg_wdata));
    }
    if ((0x40000000U & (vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata))) {
        ++(vlSymsp->__Vcoverage[42]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x40000000U & vlSelfRef.reg_wdata));
    }
    if (((vlSelfRef.reg_wdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[43]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_wdata 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_wdata) 
               | (0x80000000U & vlSelfRef.reg_wdata));
    }
    if ((1U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[82]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (1U & vlSelfRef.aes_result_i[0U]));
    }
    if ((2U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[83]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (2U & vlSelfRef.aes_result_i[0U]));
    }
    if ((4U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[84]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (4U & vlSelfRef.aes_result_i[0U]));
    }
    if ((8U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[85]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (8U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x10U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[86]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x10U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x20U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[87]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x20U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x40U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[88]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x40U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x80U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[89]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x80U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x100U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[90]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x100U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x200U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[91]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x200U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x400U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[92]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x400U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x800U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[93]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x800U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x1000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[94]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x1000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x2000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[95]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x2000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x4000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[96]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x4000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x8000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[97]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x8000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x10000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[98]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x10000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x20000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[99]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x20000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x40000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[100]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x40000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x80000U & (vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[101]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x80000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x100000U & (vlSelfRef.aes_result_i[0U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[102]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x100000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x200000U & (vlSelfRef.aes_result_i[0U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[103]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x200000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x400000U & (vlSelfRef.aes_result_i[0U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[104]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x400000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x800000U & (vlSelfRef.aes_result_i[0U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[105]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x800000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_result_i[0U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[106]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x1000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_result_i[0U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[107]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x2000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_result_i[0U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[108]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x4000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_result_i[0U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[109]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x8000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_result_i[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[110]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x10000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_result_i[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[111]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x20000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_result_i[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]))) {
        ++(vlSymsp->__Vcoverage[112]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x40000000U & vlSelfRef.aes_result_i[0U]));
    }
    if (((vlSelfRef.aes_result_i[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[113]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[0U]) 
               | (0x80000000U & vlSelfRef.aes_result_i[0U]));
    }
    if ((1U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[114]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (1U & vlSelfRef.aes_result_i[1U]));
    }
    if ((2U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[115]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (2U & vlSelfRef.aes_result_i[1U]));
    }
    if ((4U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[116]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (4U & vlSelfRef.aes_result_i[1U]));
    }
    if ((8U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[117]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (8U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x10U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[118]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x10U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x20U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[119]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x20U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x40U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[120]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x40U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x80U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[121]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x80U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x100U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[122]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x100U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x200U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[123]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x200U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x400U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[124]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x400U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x800U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[125]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x800U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x1000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[126]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x1000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x2000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[127]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x2000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x4000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[128]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x4000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x8000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[129]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x8000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x10000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[130]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x10000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x20000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[131]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x20000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x40000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[132]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x40000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x80000U & (vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[133]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x80000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x100000U & (vlSelfRef.aes_result_i[1U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[134]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x100000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x200000U & (vlSelfRef.aes_result_i[1U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[135]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x200000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x400000U & (vlSelfRef.aes_result_i[1U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[136]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x400000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x800000U & (vlSelfRef.aes_result_i[1U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[137]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x800000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_result_i[1U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[138]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x1000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_result_i[1U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[139]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x2000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_result_i[1U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[140]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x4000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_result_i[1U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[141]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x8000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_result_i[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[142]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x10000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_result_i[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[143]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x20000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_result_i[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]))) {
        ++(vlSymsp->__Vcoverage[144]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x40000000U & vlSelfRef.aes_result_i[1U]));
    }
    if (((vlSelfRef.aes_result_i[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[145]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[1U]) 
               | (0x80000000U & vlSelfRef.aes_result_i[1U]));
    }
    if ((1U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[146]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (1U & vlSelfRef.aes_result_i[2U]));
    }
    if ((2U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[147]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (2U & vlSelfRef.aes_result_i[2U]));
    }
    if ((4U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[148]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (4U & vlSelfRef.aes_result_i[2U]));
    }
    if ((8U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[149]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (8U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x10U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[150]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x10U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x20U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[151]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x20U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x40U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[152]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x40U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x80U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[153]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x80U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x100U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[154]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x100U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x200U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[155]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x200U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x400U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[156]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x400U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x800U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[157]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x800U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x1000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[158]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x1000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x2000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[159]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x2000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x4000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[160]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x4000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x8000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[161]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x8000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x10000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[162]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x10000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x20000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[163]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x20000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x40000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[164]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x40000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x80000U & (vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[165]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x80000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x100000U & (vlSelfRef.aes_result_i[2U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[166]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x100000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x200000U & (vlSelfRef.aes_result_i[2U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[167]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x200000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x400000U & (vlSelfRef.aes_result_i[2U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[168]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x400000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x800000U & (vlSelfRef.aes_result_i[2U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[169]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x800000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_result_i[2U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[170]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x1000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_result_i[2U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[171]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x2000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_result_i[2U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[172]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x4000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_result_i[2U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[173]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x8000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_result_i[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[174]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x10000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_result_i[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[175]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x20000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_result_i[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]))) {
        ++(vlSymsp->__Vcoverage[176]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x40000000U & vlSelfRef.aes_result_i[2U]));
    }
    if (((vlSelfRef.aes_result_i[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[177]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[2U]) 
               | (0x80000000U & vlSelfRef.aes_result_i[2U]));
    }
    if ((1U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[178]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (1U & vlSelfRef.aes_result_i[3U]));
    }
    if ((2U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[179]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (2U & vlSelfRef.aes_result_i[3U]));
    }
    if ((4U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[180]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (4U & vlSelfRef.aes_result_i[3U]));
    }
    if ((8U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[181]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (8U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x10U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[182]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x10U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x20U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[183]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x20U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x40U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[184]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x40U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x80U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[185]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x80U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x100U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[186]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x100U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x200U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[187]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x200U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x400U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[188]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x400U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x800U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[189]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x800U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x1000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[190]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x1000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x2000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[191]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x2000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x4000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[192]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x4000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x8000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[193]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x8000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x10000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[194]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x10000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x20000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[195]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x20000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x40000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[196]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x40000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x80000U & (vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[197]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x80000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x100000U & (vlSelfRef.aes_result_i[3U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[198]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x100000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x200000U & (vlSelfRef.aes_result_i[3U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[199]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x200000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x400000U & (vlSelfRef.aes_result_i[3U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[200]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x400000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x800000U & (vlSelfRef.aes_result_i[3U] ^ 
                      vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[201]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x800000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_result_i[3U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[202]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x1000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_result_i[3U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[203]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x2000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_result_i[3U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[204]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x4000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_result_i[3U] ^ 
                       vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[205]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x8000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_result_i[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[206]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x10000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_result_i[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[207]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x20000000U & vlSelfRef.aes_result_i[3U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_result_i[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]))) {
        ++(vlSymsp->__Vcoverage[208]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x40000000U & vlSelfRef.aes_result_i[3U]));
    }
    if (((vlSelfRef.aes_result_i[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[209]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_result_i[3U]) 
               | (0x80000000U & vlSelfRef.aes_result_i[3U]));
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__act(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG

void Vregister_map___024root___eval_triggers__act(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, ((IData)(vlSelfRef.clk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))));
    vlSelfRef.__VactTriggered.set(1U, ((IData)(vlSelfRef.rst) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vregister_map___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vregister_map___024root___nba_sequent__TOP__0(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.rst) {
        ++(vlSymsp->__Vcoverage[490]);
        vlSelfRef.reg_rdata = 0U;
        vlSelfRef.reg_ready = 0U;
        vlSelfRef.aes_start_o = 0U;
        vlSelfRef.bist_start_o = 0U;
        vlSelfRef.wdt_enable_o = 0U;
        vlSelfRef.aes_key_o[0U] = 0U;
        vlSelfRef.aes_key_o[1U] = 0U;
        vlSelfRef.aes_key_o[2U] = 0U;
        vlSelfRef.aes_key_o[3U] = 0U;
        vlSelfRef.aes_plaintext_o[0U] = 0U;
        vlSelfRef.aes_plaintext_o[1U] = 0U;
        vlSelfRef.aes_plaintext_o[2U] = 0U;
        vlSelfRef.aes_plaintext_o[3U] = 0U;
    } else {
        vlSelfRef.reg_ready = 0U;
        vlSelfRef.aes_start_o = 0U;
        vlSelfRef.bist_start_o = 0U;
        if (vlSelfRef.reg_write) {
            vlSelfRef.reg_ready = 1U;
            if (((((((((0U == (IData)(vlSelfRef.reg_addr)) 
                       | (8U == (IData)(vlSelfRef.reg_addr))) 
                      | (0xcU == (IData)(vlSelfRef.reg_addr))) 
                     | (0x10U == (IData)(vlSelfRef.reg_addr))) 
                    | (0x14U == (IData)(vlSelfRef.reg_addr))) 
                   | (0x18U == (IData)(vlSelfRef.reg_addr))) 
                  | (0x1cU == (IData)(vlSelfRef.reg_addr))) 
                 | (0x20U == (IData)(vlSelfRef.reg_addr)))) {
                if ((0U == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[469]);
                    vlSelfRef.aes_start_o = (1U & vlSelfRef.reg_wdata);
                    vlSelfRef.bist_start_o = (1U & 
                                              (vlSelfRef.reg_wdata 
                                               >> 1U));
                    vlSelfRef.wdt_enable_o = (1U & 
                                              (vlSelfRef.reg_wdata 
                                               >> 2U));
                } else if ((8U == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[470]);
                    vlSelfRef.aes_key_o[3U] = vlSelfRef.reg_wdata;
                } else if ((0xcU == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[471]);
                    vlSelfRef.aes_key_o[2U] = vlSelfRef.reg_wdata;
                } else if ((0x10U == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[472]);
                    vlSelfRef.aes_key_o[1U] = vlSelfRef.reg_wdata;
                } else if ((0x14U == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[473]);
                    vlSelfRef.aes_key_o[0U] = vlSelfRef.reg_wdata;
                } else if ((0x18U == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[474]);
                    vlSelfRef.aes_plaintext_o[3U] = vlSelfRef.reg_wdata;
                } else if ((0x1cU == (IData)(vlSelfRef.reg_addr))) {
                    ++(vlSymsp->__Vcoverage[475]);
                    vlSelfRef.aes_plaintext_o[2U] = vlSelfRef.reg_wdata;
                } else {
                    ++(vlSymsp->__Vcoverage[476]);
                    vlSelfRef.aes_plaintext_o[1U] = vlSelfRef.reg_wdata;
                }
            } else if ((0x24U == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[477]);
                vlSelfRef.aes_plaintext_o[0U] = vlSelfRef.reg_wdata;
            } else {
                ++(vlSymsp->__Vcoverage[478]);
            }
            ++(vlSymsp->__Vcoverage[479]);
        } else {
            ++(vlSymsp->__Vcoverage[480]);
        }
        if (vlSelfRef.reg_read) {
            vlSelfRef.reg_ready = 1U;
            if ((4U == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[481]);
                vlSelfRef.reg_rdata = (((IData)(vlSelfRef.glitch_detected_i) 
                                        << 4U) | ((
                                                   ((IData)(vlSelfRef.wdt_timeout_i) 
                                                    << 3U) 
                                                   | ((IData)(vlSelfRef.bist_fail_i) 
                                                      << 2U)) 
                                                  | (((IData)(vlSelfRef.bist_pass_i) 
                                                      << 1U) 
                                                     | (IData)(vlSelfRef.aes_done_i))));
            } else if ((0x28U == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[482]);
                vlSelfRef.reg_rdata = vlSelfRef.aes_result_i[3U];
            } else if ((0x2cU == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[483]);
                vlSelfRef.reg_rdata = vlSelfRef.aes_result_i[2U];
            } else if ((0x30U == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[484]);
                vlSelfRef.reg_rdata = vlSelfRef.aes_result_i[1U];
            } else if ((0x34U == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[485]);
                vlSelfRef.reg_rdata = vlSelfRef.aes_result_i[0U];
            } else if ((0xfcU == (IData)(vlSelfRef.reg_addr))) {
                ++(vlSymsp->__Vcoverage[486]);
                vlSelfRef.reg_rdata = 0x4e45454cU;
            } else {
                ++(vlSymsp->__Vcoverage[487]);
                vlSelfRef.reg_rdata = 0U;
            }
            ++(vlSymsp->__Vcoverage[488]);
        } else {
            ++(vlSymsp->__Vcoverage[489]);
        }
        ++(vlSymsp->__Vcoverage[491]);
    }
    ++(vlSymsp->__Vcoverage[492]);
    if (((IData)(vlSelfRef.reg_ready) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_ready))) {
        ++(vlSymsp->__Vcoverage[76]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_ready 
            = vlSelfRef.reg_ready;
    }
    if (((IData)(vlSelfRef.aes_start_o) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__aes_start_o))) {
        ++(vlSymsp->__Vcoverage[210]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_start_o 
            = vlSelfRef.aes_start_o;
    }
    if (((IData)(vlSelfRef.bist_start_o) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__bist_start_o))) {
        ++(vlSymsp->__Vcoverage[211]);
        vlSelfRef.register_map__DOT____Vtogcov__bist_start_o 
            = vlSelfRef.bist_start_o;
    }
    if (((IData)(vlSelfRef.wdt_enable_o) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__wdt_enable_o))) {
        ++(vlSymsp->__Vcoverage[212]);
        vlSelfRef.register_map__DOT____Vtogcov__wdt_enable_o 
            = vlSelfRef.wdt_enable_o;
    }
    if ((1U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[44]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (1U & vlSelfRef.reg_rdata));
    }
    if ((2U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[45]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (2U & vlSelfRef.reg_rdata));
    }
    if ((4U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[46]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (4U & vlSelfRef.reg_rdata));
    }
    if ((8U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[47]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (8U & vlSelfRef.reg_rdata));
    }
    if ((0x10U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[48]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x10U & vlSelfRef.reg_rdata));
    }
    if ((0x20U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[49]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x20U & vlSelfRef.reg_rdata));
    }
    if ((0x40U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[50]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x40U & vlSelfRef.reg_rdata));
    }
    if ((0x80U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[51]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x80U & vlSelfRef.reg_rdata));
    }
    if ((0x100U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[52]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x100U & vlSelfRef.reg_rdata));
    }
    if ((0x200U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[53]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x200U & vlSelfRef.reg_rdata));
    }
    if ((0x400U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[54]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x400U & vlSelfRef.reg_rdata));
    }
    if ((0x800U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[55]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x800U & vlSelfRef.reg_rdata));
    }
    if ((0x1000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[56]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x1000U & vlSelfRef.reg_rdata));
    }
    if ((0x2000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[57]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x2000U & vlSelfRef.reg_rdata));
    }
    if ((0x4000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[58]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x4000U & vlSelfRef.reg_rdata));
    }
    if ((0x8000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[59]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x8000U & vlSelfRef.reg_rdata));
    }
    if ((0x10000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[60]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x10000U & vlSelfRef.reg_rdata));
    }
    if ((0x20000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[61]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x20000U & vlSelfRef.reg_rdata));
    }
    if ((0x40000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[62]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x40000U & vlSelfRef.reg_rdata));
    }
    if ((0x80000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[63]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x80000U & vlSelfRef.reg_rdata));
    }
    if ((0x100000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[64]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x100000U & vlSelfRef.reg_rdata));
    }
    if ((0x200000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[65]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x200000U & vlSelfRef.reg_rdata));
    }
    if ((0x400000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[66]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x400000U & vlSelfRef.reg_rdata));
    }
    if ((0x800000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[67]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x800000U & vlSelfRef.reg_rdata));
    }
    if ((0x1000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[68]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x1000000U & vlSelfRef.reg_rdata));
    }
    if ((0x2000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[69]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x2000000U & vlSelfRef.reg_rdata));
    }
    if ((0x4000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[70]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x4000000U & vlSelfRef.reg_rdata));
    }
    if ((0x8000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[71]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x8000000U & vlSelfRef.reg_rdata));
    }
    if ((0x10000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[72]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x10000000U & vlSelfRef.reg_rdata));
    }
    if ((0x20000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[73]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x20000000U & vlSelfRef.reg_rdata));
    }
    if ((0x40000000U & (vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata))) {
        ++(vlSymsp->__Vcoverage[74]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x40000000U & vlSelfRef.reg_rdata));
    }
    if (((vlSelfRef.reg_rdata ^ vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[75]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_rdata 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__reg_rdata) 
               | (0x80000000U & vlSelfRef.reg_rdata));
    }
    if ((1U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[213]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (1U & vlSelfRef.aes_key_o[0U]));
    }
    if ((2U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[214]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (2U & vlSelfRef.aes_key_o[0U]));
    }
    if ((4U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[215]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (4U & vlSelfRef.aes_key_o[0U]));
    }
    if ((8U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[216]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (8U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x10U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[217]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x10U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x20U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[218]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x20U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x40U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[219]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x40U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x80U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[220]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x80U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x100U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[221]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x100U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x200U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[222]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x200U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x400U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[223]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x400U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x800U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[224]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x800U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x1000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[225]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x1000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x2000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[226]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x2000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x4000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[227]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x4000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x8000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[228]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x8000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x10000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[229]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x10000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x20000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[230]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x20000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x40000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[231]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x40000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x80000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[232]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x80000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x100000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[233]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x100000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x200000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[234]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x200000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x400000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[235]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x400000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x800000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[236]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x800000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[237]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x1000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[238]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x2000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[239]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x4000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[240]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x8000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[241]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x10000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[242]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x20000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]))) {
        ++(vlSymsp->__Vcoverage[243]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x40000000U & vlSelfRef.aes_key_o[0U]));
    }
    if (((vlSelfRef.aes_key_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[244]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[0U]) 
               | (0x80000000U & vlSelfRef.aes_key_o[0U]));
    }
    if ((1U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[245]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (1U & vlSelfRef.aes_key_o[1U]));
    }
    if ((2U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[246]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (2U & vlSelfRef.aes_key_o[1U]));
    }
    if ((4U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[247]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (4U & vlSelfRef.aes_key_o[1U]));
    }
    if ((8U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[248]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (8U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x10U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[249]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x10U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x20U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[250]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x20U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x40U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[251]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x40U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x80U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[252]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x80U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x100U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[253]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x100U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x200U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[254]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x200U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x400U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[255]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x400U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x800U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[256]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x800U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x1000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[257]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x1000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x2000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[258]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x2000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x4000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[259]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x4000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x8000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[260]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x8000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x10000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[261]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x10000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x20000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[262]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x20000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x40000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[263]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x40000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x80000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[264]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x80000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x100000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[265]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x100000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x200000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[266]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x200000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x400000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[267]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x400000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x800000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[268]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x800000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[269]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x1000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[270]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x2000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[271]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x4000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[272]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x8000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[273]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x10000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[274]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x20000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]))) {
        ++(vlSymsp->__Vcoverage[275]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x40000000U & vlSelfRef.aes_key_o[1U]));
    }
    if (((vlSelfRef.aes_key_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[276]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[1U]) 
               | (0x80000000U & vlSelfRef.aes_key_o[1U]));
    }
    if ((1U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[277]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (1U & vlSelfRef.aes_key_o[2U]));
    }
    if ((2U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[278]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (2U & vlSelfRef.aes_key_o[2U]));
    }
    if ((4U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[279]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (4U & vlSelfRef.aes_key_o[2U]));
    }
    if ((8U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[280]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (8U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x10U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[281]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x10U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x20U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[282]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x20U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x40U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[283]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x40U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x80U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[284]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x80U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x100U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[285]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x100U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x200U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[286]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x200U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x400U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[287]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x400U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x800U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[288]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x800U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x1000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[289]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x1000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x2000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[290]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x2000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x4000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[291]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x4000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x8000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[292]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x8000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x10000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[293]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x10000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x20000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[294]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x20000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x40000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[295]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x40000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x80000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[296]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x80000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x100000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[297]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x100000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x200000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[298]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x200000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x400000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[299]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x400000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x800000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[300]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x800000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[301]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x1000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[302]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x2000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[303]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x4000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[304]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x8000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[305]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x10000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[306]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x20000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]))) {
        ++(vlSymsp->__Vcoverage[307]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x40000000U & vlSelfRef.aes_key_o[2U]));
    }
    if (((vlSelfRef.aes_key_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[308]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[2U]) 
               | (0x80000000U & vlSelfRef.aes_key_o[2U]));
    }
    if ((1U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[309]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (1U & vlSelfRef.aes_key_o[3U]));
    }
    if ((2U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[310]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (2U & vlSelfRef.aes_key_o[3U]));
    }
    if ((4U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[311]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (4U & vlSelfRef.aes_key_o[3U]));
    }
    if ((8U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[312]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (8U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x10U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[313]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x10U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x20U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[314]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x20U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x40U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[315]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x40U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x80U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[316]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x80U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x100U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[317]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x100U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x200U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[318]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x200U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x400U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[319]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x400U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x800U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[320]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x800U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x1000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[321]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x1000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x2000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[322]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x2000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x4000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[323]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x4000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x8000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[324]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x8000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x10000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[325]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x10000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x20000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[326]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x20000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x40000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[327]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x40000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x80000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[328]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x80000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x100000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[329]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x100000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x200000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[330]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x200000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x400000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[331]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x400000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x800000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[332]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x800000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[333]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x1000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[334]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x2000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[335]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x4000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[336]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x8000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[337]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x10000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[338]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x20000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]))) {
        ++(vlSymsp->__Vcoverage[339]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x40000000U & vlSelfRef.aes_key_o[3U]));
    }
    if (((vlSelfRef.aes_key_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[340]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_key_o[3U]) 
               | (0x80000000U & vlSelfRef.aes_key_o[3U]));
    }
    if ((1U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[341]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (1U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((2U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[342]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (2U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((4U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[343]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (4U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((8U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[344]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (8U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x10U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[345]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x10U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x20U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[346]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x20U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x40U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[347]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x40U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x80U & (vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[348]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x80U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x100U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[349]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x100U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x200U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[350]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x200U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x400U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[351]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x400U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x800U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[352]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x800U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x1000U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[353]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x1000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x2000U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[354]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x2000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x4000U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[355]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x4000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x8000U & (vlSelfRef.aes_plaintext_o[0U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[356]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x8000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x10000U & (vlSelfRef.aes_plaintext_o[0U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[357]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x10000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x20000U & (vlSelfRef.aes_plaintext_o[0U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[358]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x20000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x40000U & (vlSelfRef.aes_plaintext_o[0U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[359]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x40000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x80000U & (vlSelfRef.aes_plaintext_o[0U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[360]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x80000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x100000U & (vlSelfRef.aes_plaintext_o[0U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[361]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x100000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x200000U & (vlSelfRef.aes_plaintext_o[0U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[362]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x200000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x400000U & (vlSelfRef.aes_plaintext_o[0U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[363]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x400000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x800000U & (vlSelfRef.aes_plaintext_o[0U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[364]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x800000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_plaintext_o[0U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[365]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x1000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_plaintext_o[0U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[366]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x2000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_plaintext_o[0U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[367]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x4000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_plaintext_o[0U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[368]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x8000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_plaintext_o[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[369]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x10000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_plaintext_o[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[370]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x20000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_plaintext_o[0U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]))) {
        ++(vlSymsp->__Vcoverage[371]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x40000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if (((vlSelfRef.aes_plaintext_o[0U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[372]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[0U]) 
               | (0x80000000U & vlSelfRef.aes_plaintext_o[0U]));
    }
    if ((1U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[373]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (1U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((2U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[374]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (2U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((4U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[375]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (4U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((8U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[376]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (8U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x10U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[377]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x10U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x20U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[378]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x20U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x40U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[379]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x40U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x80U & (vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[380]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x80U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x100U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[381]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x100U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x200U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[382]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x200U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x400U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[383]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x400U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x800U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[384]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x800U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x1000U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[385]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x1000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x2000U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[386]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x2000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x4000U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[387]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x4000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x8000U & (vlSelfRef.aes_plaintext_o[1U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[388]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x8000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x10000U & (vlSelfRef.aes_plaintext_o[1U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[389]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x10000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x20000U & (vlSelfRef.aes_plaintext_o[1U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[390]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x20000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x40000U & (vlSelfRef.aes_plaintext_o[1U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[391]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x40000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x80000U & (vlSelfRef.aes_plaintext_o[1U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[392]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x80000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x100000U & (vlSelfRef.aes_plaintext_o[1U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[393]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x100000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x200000U & (vlSelfRef.aes_plaintext_o[1U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[394]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x200000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x400000U & (vlSelfRef.aes_plaintext_o[1U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[395]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x400000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x800000U & (vlSelfRef.aes_plaintext_o[1U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[396]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x800000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_plaintext_o[1U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[397]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x1000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_plaintext_o[1U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[398]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x2000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_plaintext_o[1U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[399]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x4000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_plaintext_o[1U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[400]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x8000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_plaintext_o[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[401]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x10000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_plaintext_o[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[402]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x20000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_plaintext_o[1U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]))) {
        ++(vlSymsp->__Vcoverage[403]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x40000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if (((vlSelfRef.aes_plaintext_o[1U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[404]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[1U]) 
               | (0x80000000U & vlSelfRef.aes_plaintext_o[1U]));
    }
    if ((1U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[405]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (1U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((2U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[406]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (2U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((4U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[407]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (4U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((8U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[408]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (8U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x10U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[409]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x10U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x20U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[410]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x20U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x40U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[411]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x40U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x80U & (vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[412]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x80U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x100U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[413]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x100U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x200U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[414]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x200U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x400U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[415]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x400U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x800U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[416]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x800U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x1000U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[417]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x1000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x2000U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[418]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x2000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x4000U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[419]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x4000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x8000U & (vlSelfRef.aes_plaintext_o[2U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[420]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x8000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x10000U & (vlSelfRef.aes_plaintext_o[2U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[421]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x10000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x20000U & (vlSelfRef.aes_plaintext_o[2U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[422]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x20000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x40000U & (vlSelfRef.aes_plaintext_o[2U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[423]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x40000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x80000U & (vlSelfRef.aes_plaintext_o[2U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[424]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x80000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x100000U & (vlSelfRef.aes_plaintext_o[2U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[425]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x100000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x200000U & (vlSelfRef.aes_plaintext_o[2U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[426]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x200000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x400000U & (vlSelfRef.aes_plaintext_o[2U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[427]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x400000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x800000U & (vlSelfRef.aes_plaintext_o[2U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[428]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x800000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_plaintext_o[2U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[429]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x1000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_plaintext_o[2U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[430]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x2000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_plaintext_o[2U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[431]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x4000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_plaintext_o[2U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[432]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x8000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_plaintext_o[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[433]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x10000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_plaintext_o[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[434]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x20000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_plaintext_o[2U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]))) {
        ++(vlSymsp->__Vcoverage[435]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x40000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if (((vlSelfRef.aes_plaintext_o[2U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[436]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[2U]) 
               | (0x80000000U & vlSelfRef.aes_plaintext_o[2U]));
    }
    if ((1U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[437]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffffeU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (1U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((2U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[438]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffffdU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (2U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((4U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[439]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffffbU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (4U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((8U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[440]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffff7U & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (8U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x10U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[441]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffffefU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x10U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x20U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[442]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffffdfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x20U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x40U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[443]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffffbfU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x40U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x80U & (vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[444]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffff7fU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x80U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x100U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[445]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffeffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x100U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x200U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[446]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffdffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x200U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x400U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[447]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffffbffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x400U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x800U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                   vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[448]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffff7ffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x800U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x1000U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[449]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffefffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x1000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x2000U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[450]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffdfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x2000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x4000U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[451]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffffbfffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x4000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x8000U & (vlSelfRef.aes_plaintext_o[3U] ^ 
                    vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[452]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffff7fffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x8000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x10000U & (vlSelfRef.aes_plaintext_o[3U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[453]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffeffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x10000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x20000U & (vlSelfRef.aes_plaintext_o[3U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[454]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffdffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x20000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x40000U & (vlSelfRef.aes_plaintext_o[3U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[455]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfffbffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x40000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x80000U & (vlSelfRef.aes_plaintext_o[3U] 
                     ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[456]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfff7ffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x80000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x100000U & (vlSelfRef.aes_plaintext_o[3U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[457]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffefffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x100000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x200000U & (vlSelfRef.aes_plaintext_o[3U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[458]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffdfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x200000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x400000U & (vlSelfRef.aes_plaintext_o[3U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[459]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xffbfffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x400000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x800000U & (vlSelfRef.aes_plaintext_o[3U] 
                      ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[460]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xff7fffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x800000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x1000000U & (vlSelfRef.aes_plaintext_o[3U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[461]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfeffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x1000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x2000000U & (vlSelfRef.aes_plaintext_o[3U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[462]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfdffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x2000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x4000000U & (vlSelfRef.aes_plaintext_o[3U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[463]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xfbffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x4000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x8000000U & (vlSelfRef.aes_plaintext_o[3U] 
                       ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[464]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xf7ffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x8000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x10000000U & (vlSelfRef.aes_plaintext_o[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[465]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xefffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x10000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x20000000U & (vlSelfRef.aes_plaintext_o[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[466]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xdfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x20000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if ((0x40000000U & (vlSelfRef.aes_plaintext_o[3U] 
                        ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]))) {
        ++(vlSymsp->__Vcoverage[467]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0xbfffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x40000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
    if (((vlSelfRef.aes_plaintext_o[3U] ^ vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
         >> 0x1fU)) {
        ++(vlSymsp->__Vcoverage[468]);
        vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U] 
            = ((0x7fffffffU & vlSelfRef.register_map__DOT____Vtogcov__aes_plaintext_o[3U]) 
               | (0x80000000U & vlSelfRef.aes_plaintext_o[3U]));
    }
}
