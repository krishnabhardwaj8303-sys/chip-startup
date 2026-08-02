// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vregister_map.h for the primary calling header

#include "Vregister_map__pch.h"
#include "Vregister_map__Syms.h"
#include "Vregister_map___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__stl(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vregister_map___024root___eval_triggers__stl(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vregister_map___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vregister_map___024root___stl_sequent__TOP__0(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___stl_sequent__TOP__0\n"); );
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
    if (((IData)(vlSelfRef.reg_ready) ^ (IData)(vlSelfRef.register_map__DOT____Vtogcov__reg_ready))) {
        ++(vlSymsp->__Vcoverage[76]);
        vlSelfRef.register_map__DOT____Vtogcov__reg_ready 
            = vlSelfRef.reg_ready;
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

VL_ATTR_COLD void Vregister_map___024root___configure_coverage(Vregister_map___024root* vlSelf, bool first) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___configure_coverage\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "register_map.v", 2, 24, ".register_map", "v_toggle/register_map", "clk", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "register_map.v", 3, 24, ".register_map", "v_toggle/register_map", "rst", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "register_map.v", 5, 24, ".register_map", "v_toggle/register_map", "reg_write", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "register_map.v", 6, 24, ".register_map", "v_toggle/register_map", "reg_read", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "register_map.v", 7, 24, ".register_map", "v_toggle/register_map", "reg_addr[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[8]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[9]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[10]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[11]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[12]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[13]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[26]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[14]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[27]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[15]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[28]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[16]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[29]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[17]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[30]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[18]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[31]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[19]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[32]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[20]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[33]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[21]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[34]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[22]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[35]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[23]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[36]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[24]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[37]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[25]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[38]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[26]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[39]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[27]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[40]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[28]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[41]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[29]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[42]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[30]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[43]), first, "register_map.v", 8, 24, ".register_map", "v_toggle/register_map", "reg_wdata[31]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[44]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[45]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[46]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[47]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[48]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[49]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[50]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[51]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[52]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[8]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[53]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[9]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[54]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[10]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[55]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[11]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[56]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[12]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[57]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[13]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[58]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[14]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[59]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[15]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[60]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[16]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[61]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[17]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[62]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[18]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[63]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[19]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[64]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[20]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[65]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[21]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[66]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[22]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[67]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[23]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[68]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[24]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[69]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[25]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[70]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[26]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[71]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[27]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[72]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[28]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[73]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[29]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[74]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[30]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[75]), first, "register_map.v", 9, 24, ".register_map", "v_toggle/register_map", "reg_rdata[31]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[76]), first, "register_map.v", 10, 24, ".register_map", "v_toggle/register_map", "reg_ready", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[77]), first, "register_map.v", 13, 24, ".register_map", "v_toggle/register_map", "bist_pass_i", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[78]), first, "register_map.v", 14, 24, ".register_map", "v_toggle/register_map", "bist_fail_i", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[79]), first, "register_map.v", 15, 24, ".register_map", "v_toggle/register_map", "wdt_timeout_i", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[80]), first, "register_map.v", 16, 24, ".register_map", "v_toggle/register_map", "glitch_detected_i", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[81]), first, "register_map.v", 17, 24, ".register_map", "v_toggle/register_map", "aes_done_i", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[82]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[83]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[84]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[85]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[86]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[87]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[88]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[89]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[90]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[8]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[91]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[9]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[92]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[10]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[93]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[11]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[94]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[12]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[95]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[13]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[96]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[14]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[97]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[15]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[98]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[16]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[99]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[17]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[100]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[18]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[101]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[19]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[102]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[20]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[103]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[21]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[104]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[22]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[105]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[23]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[106]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[24]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[107]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[25]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[108]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[26]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[109]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[27]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[110]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[28]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[111]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[29]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[112]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[30]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[113]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[31]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[114]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[32]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[115]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[33]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[116]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[34]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[117]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[35]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[118]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[36]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[119]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[37]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[120]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[38]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[121]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[39]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[122]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[40]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[123]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[41]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[124]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[42]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[125]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[43]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[126]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[44]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[127]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[45]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[128]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[46]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[129]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[47]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[130]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[48]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[131]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[49]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[132]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[50]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[133]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[51]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[134]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[52]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[135]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[53]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[136]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[54]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[137]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[55]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[138]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[56]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[139]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[57]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[140]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[58]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[141]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[59]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[142]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[60]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[143]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[61]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[144]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[62]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[145]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[63]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[146]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[64]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[147]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[65]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[148]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[66]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[149]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[67]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[150]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[68]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[151]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[69]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[152]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[70]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[153]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[71]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[154]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[72]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[155]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[73]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[156]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[74]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[157]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[75]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[158]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[76]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[159]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[77]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[160]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[78]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[161]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[79]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[162]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[80]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[163]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[81]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[164]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[82]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[165]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[83]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[166]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[84]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[167]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[85]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[168]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[86]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[169]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[87]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[170]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[88]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[171]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[89]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[172]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[90]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[173]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[91]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[174]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[92]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[175]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[93]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[176]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[94]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[177]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[95]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[178]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[96]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[179]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[97]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[180]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[98]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[181]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[99]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[182]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[100]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[183]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[101]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[184]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[102]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[185]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[103]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[186]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[104]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[187]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[105]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[188]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[106]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[189]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[107]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[190]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[108]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[191]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[109]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[192]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[110]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[193]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[111]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[194]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[112]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[195]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[113]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[196]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[114]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[197]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[115]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[198]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[116]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[199]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[117]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[200]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[118]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[201]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[119]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[202]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[120]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[203]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[121]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[204]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[122]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[205]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[123]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[206]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[124]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[207]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[125]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[208]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[126]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[209]), first, "register_map.v", 18, 25, ".register_map", "v_toggle/register_map", "aes_result_i[127]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[210]), first, "register_map.v", 22, 24, ".register_map", "v_toggle/register_map", "aes_start_o", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[211]), first, "register_map.v", 23, 24, ".register_map", "v_toggle/register_map", "bist_start_o", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[212]), first, "register_map.v", 24, 24, ".register_map", "v_toggle/register_map", "wdt_enable_o", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[213]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[214]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[215]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[216]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[217]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[218]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[219]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[220]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[221]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[8]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[222]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[9]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[223]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[10]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[224]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[11]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[225]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[12]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[226]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[13]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[227]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[14]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[228]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[15]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[229]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[16]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[230]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[17]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[231]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[18]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[232]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[19]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[233]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[20]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[234]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[21]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[235]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[22]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[236]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[23]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[237]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[24]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[238]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[25]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[239]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[26]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[240]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[27]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[241]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[28]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[242]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[29]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[243]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[30]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[244]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[31]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[245]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[32]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[246]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[33]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[247]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[34]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[248]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[35]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[249]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[36]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[250]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[37]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[251]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[38]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[252]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[39]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[253]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[40]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[254]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[41]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[255]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[42]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[256]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[43]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[257]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[44]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[258]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[45]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[259]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[46]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[260]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[47]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[261]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[48]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[262]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[49]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[263]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[50]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[264]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[51]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[265]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[52]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[266]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[53]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[267]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[54]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[268]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[55]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[269]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[56]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[270]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[57]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[271]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[58]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[272]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[59]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[273]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[60]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[274]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[61]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[275]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[62]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[276]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[63]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[277]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[64]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[278]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[65]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[279]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[66]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[280]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[67]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[281]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[68]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[282]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[69]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[283]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[70]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[284]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[71]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[285]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[72]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[286]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[73]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[287]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[74]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[288]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[75]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[289]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[76]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[290]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[77]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[291]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[78]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[292]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[79]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[293]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[80]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[294]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[81]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[295]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[82]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[296]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[83]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[297]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[84]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[298]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[85]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[299]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[86]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[300]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[87]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[301]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[88]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[302]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[89]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[303]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[90]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[304]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[91]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[305]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[92]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[306]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[93]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[307]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[94]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[308]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[95]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[309]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[96]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[310]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[97]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[311]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[98]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[312]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[99]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[313]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[100]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[314]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[101]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[315]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[102]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[316]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[103]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[317]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[104]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[318]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[105]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[319]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[106]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[320]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[107]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[321]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[108]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[322]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[109]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[323]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[110]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[324]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[111]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[325]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[112]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[326]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[113]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[327]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[114]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[328]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[115]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[329]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[116]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[330]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[117]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[331]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[118]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[332]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[119]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[333]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[120]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[334]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[121]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[335]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[122]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[336]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[123]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[337]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[124]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[338]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[125]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[339]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[126]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[340]), first, "register_map.v", 25, 25, ".register_map", "v_toggle/register_map", "aes_key_o[127]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[341]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[0]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[342]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[1]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[343]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[2]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[344]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[3]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[345]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[4]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[346]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[5]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[347]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[6]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[348]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[7]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[349]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[8]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[350]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[9]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[351]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[10]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[352]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[11]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[353]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[12]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[354]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[13]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[355]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[14]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[356]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[15]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[357]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[16]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[358]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[17]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[359]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[18]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[360]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[19]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[361]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[20]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[362]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[21]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[363]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[22]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[364]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[23]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[365]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[24]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[366]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[25]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[367]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[26]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[368]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[27]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[369]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[28]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[370]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[29]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[371]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[30]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[372]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[31]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[373]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[32]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[374]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[33]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[375]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[34]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[376]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[35]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[377]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[36]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[378]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[37]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[379]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[38]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[380]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[39]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[381]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[40]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[382]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[41]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[383]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[42]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[384]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[43]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[385]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[44]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[386]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[45]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[387]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[46]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[388]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[47]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[389]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[48]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[390]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[49]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[391]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[50]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[392]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[51]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[393]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[52]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[394]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[53]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[395]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[54]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[396]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[55]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[397]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[56]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[398]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[57]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[399]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[58]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[400]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[59]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[401]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[60]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[402]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[61]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[403]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[62]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[404]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[63]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[405]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[64]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[406]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[65]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[407]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[66]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[408]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[67]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[409]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[68]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[410]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[69]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[411]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[70]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[412]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[71]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[413]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[72]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[414]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[73]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[415]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[74]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[416]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[75]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[417]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[76]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[418]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[77]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[419]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[78]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[420]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[79]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[421]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[80]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[422]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[81]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[423]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[82]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[424]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[83]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[425]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[84]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[426]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[85]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[427]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[86]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[428]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[87]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[429]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[88]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[430]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[89]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[431]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[90]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[432]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[91]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[433]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[92]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[434]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[93]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[435]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[94]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[436]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[95]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[437]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[96]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[438]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[97]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[439]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[98]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[440]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[99]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[441]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[100]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[442]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[101]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[443]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[102]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[444]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[103]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[445]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[104]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[446]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[105]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[447]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[106]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[448]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[107]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[449]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[108]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[450]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[109]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[451]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[110]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[452]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[111]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[453]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[112]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[454]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[113]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[455]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[114]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[456]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[115]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[457]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[116]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[458]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[117]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[459]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[118]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[460]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[119]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[461]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[120]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[462]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[121]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[463]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[122]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[464]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[123]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[465]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[124]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[466]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[125]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[467]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[126]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[468]), first, "register_map.v", 26, 25, ".register_map", "v_toggle/register_map", "aes_plaintext_o[127]", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[469]), first, "register_map.v", 81, 33, ".register_map", "v_line/register_map", "case", "81-84");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[470]), first, "register_map.v", 86, 31, ".register_map", "v_line/register_map", "case", "86");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[471]), first, "register_map.v", 87, 31, ".register_map", "v_line/register_map", "case", "87");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[472]), first, "register_map.v", 88, 31, ".register_map", "v_line/register_map", "case", "88");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[473]), first, "register_map.v", 89, 31, ".register_map", "v_line/register_map", "case", "89");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[474]), first, "register_map.v", 90, 33, ".register_map", "v_line/register_map", "case", "90");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[475]), first, "register_map.v", 91, 33, ".register_map", "v_line/register_map", "case", "91");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[476]), first, "register_map.v", 92, 33, ".register_map", "v_line/register_map", "case", "92");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[477]), first, "register_map.v", 93, 33, ".register_map", "v_line/register_map", "case", "93");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[478]), first, "register_map.v", 94, 21, ".register_map", "v_line/register_map", "case", "94");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[479]), first, "register_map.v", 78, 13, ".register_map", "v_branch/register_map", "if", "78-80");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[480]), first, "register_map.v", 78, 14, ".register_map", "v_branch/register_map", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[481]), first, "register_map.v", 102, 32, ".register_map", "v_line/register_map", "case", "102-107");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[482]), first, "register_map.v", 108, 34, ".register_map", "v_line/register_map", "case", "108");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[483]), first, "register_map.v", 109, 34, ".register_map", "v_line/register_map", "case", "109");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[484]), first, "register_map.v", 110, 34, ".register_map", "v_line/register_map", "case", "110");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[485]), first, "register_map.v", 111, 34, ".register_map", "v_line/register_map", "case", "111");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[486]), first, "register_map.v", 112, 33, ".register_map", "v_line/register_map", "case", "112");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[487]), first, "register_map.v", 113, 21, ".register_map", "v_line/register_map", "case", "113");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[488]), first, "register_map.v", 99, 13, ".register_map", "v_branch/register_map", "if", "99-101");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[489]), first, "register_map.v", 99, 14, ".register_map", "v_branch/register_map", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[490]), first, "register_map.v", 63, 9, ".register_map", "v_branch/register_map", "if", "63-70");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[491]), first, "register_map.v", 63, 10, ".register_map", "v_branch/register_map", "else", "72-75");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[492]), first, "register_map.v", 62, 5, ".register_map", "v_line/register_map", "block", "62");
}
