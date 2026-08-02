// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vregister_map.h for the primary calling header

#include "Vregister_map__pch.h"
#include "Vregister_map___024root.h"

VL_ATTR_COLD void Vregister_map___024root___eval_static(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vregister_map___024root___eval_initial(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

VL_ATTR_COLD void Vregister_map___024root___eval_final(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__stl(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vregister_map___024root___eval_phase__stl(Vregister_map___024root* vlSelf);

VL_ATTR_COLD void Vregister_map___024root___eval_settle(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vregister_map___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("register_map.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vregister_map___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__stl(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vregister_map___024root___stl_sequent__TOP__0(Vregister_map___024root* vlSelf);

VL_ATTR_COLD void Vregister_map___024root___eval_stl(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vregister_map___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vregister_map___024root___eval_triggers__stl(Vregister_map___024root* vlSelf);

VL_ATTR_COLD bool Vregister_map___024root___eval_phase__stl(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vregister_map___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vregister_map___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__ico(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___dump_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__act(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge rst)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__nba(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge rst)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vregister_map___024root___ctor_var_reset(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->reg_write = VL_RAND_RESET_I(1);
    vlSelf->reg_read = VL_RAND_RESET_I(1);
    vlSelf->reg_addr = VL_RAND_RESET_I(8);
    vlSelf->reg_wdata = VL_RAND_RESET_I(32);
    vlSelf->reg_rdata = VL_RAND_RESET_I(32);
    vlSelf->reg_ready = VL_RAND_RESET_I(1);
    vlSelf->bist_pass_i = VL_RAND_RESET_I(1);
    vlSelf->bist_fail_i = VL_RAND_RESET_I(1);
    vlSelf->wdt_timeout_i = VL_RAND_RESET_I(1);
    vlSelf->glitch_detected_i = VL_RAND_RESET_I(1);
    vlSelf->aes_done_i = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->aes_result_i);
    vlSelf->aes_start_o = VL_RAND_RESET_I(1);
    vlSelf->bist_start_o = VL_RAND_RESET_I(1);
    vlSelf->wdt_enable_o = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->aes_key_o);
    VL_RAND_RESET_W(128, vlSelf->aes_plaintext_o);
    vlSelf->register_map__DOT____Vtogcov__clk = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__rst = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__reg_write = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__reg_read = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__reg_addr = VL_RAND_RESET_I(8);
    vlSelf->register_map__DOT____Vtogcov__reg_wdata = VL_RAND_RESET_I(32);
    vlSelf->register_map__DOT____Vtogcov__reg_rdata = VL_RAND_RESET_I(32);
    vlSelf->register_map__DOT____Vtogcov__reg_ready = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__bist_pass_i = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__bist_fail_i = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__wdt_timeout_i = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__glitch_detected_i = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__aes_done_i = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->register_map__DOT____Vtogcov__aes_result_i);
    vlSelf->register_map__DOT____Vtogcov__aes_start_o = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__bist_start_o = VL_RAND_RESET_I(1);
    vlSelf->register_map__DOT____Vtogcov__wdt_enable_o = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->register_map__DOT____Vtogcov__aes_key_o);
    VL_RAND_RESET_W(128, vlSelf->register_map__DOT____Vtogcov__aes_plaintext_o);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = VL_RAND_RESET_I(1);
}
