// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vregister_map.h for the primary calling header

#include "Vregister_map__pch.h"
#include "Vregister_map___024root.h"

void Vregister_map___024root___ico_sequent__TOP__0(Vregister_map___024root* vlSelf);

void Vregister_map___024root___eval_ico(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vregister_map___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vregister_map___024root___eval_triggers__ico(Vregister_map___024root* vlSelf);

bool Vregister_map___024root___eval_phase__ico(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vregister_map___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vregister_map___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vregister_map___024root___eval_act(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vregister_map___024root___nba_sequent__TOP__0(Vregister_map___024root* vlSelf);

void Vregister_map___024root___eval_nba(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vregister_map___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vregister_map___024root___eval_triggers__act(Vregister_map___024root* vlSelf);

bool Vregister_map___024root___eval_phase__act(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vregister_map___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vregister_map___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vregister_map___024root___eval_phase__nba(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vregister_map___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__ico(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__nba(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vregister_map___024root___dump_triggers__act(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG

void Vregister_map___024root___eval(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vregister_map___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("register_map.v", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vregister_map___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vregister_map___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("register_map.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vregister_map___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("register_map.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vregister_map___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vregister_map___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vregister_map___024root___eval_debug_assertions(Vregister_map___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vregister_map__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vregister_map___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelfRef.rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelfRef.reg_write & 0xfeU))) {
        Verilated::overWidthError("reg_write");}
    if (VL_UNLIKELY((vlSelfRef.reg_read & 0xfeU))) {
        Verilated::overWidthError("reg_read");}
    if (VL_UNLIKELY((vlSelfRef.bist_pass_i & 0xfeU))) {
        Verilated::overWidthError("bist_pass_i");}
    if (VL_UNLIKELY((vlSelfRef.bist_fail_i & 0xfeU))) {
        Verilated::overWidthError("bist_fail_i");}
    if (VL_UNLIKELY((vlSelfRef.wdt_timeout_i & 0xfeU))) {
        Verilated::overWidthError("wdt_timeout_i");}
    if (VL_UNLIKELY((vlSelfRef.glitch_detected_i & 0xfeU))) {
        Verilated::overWidthError("glitch_detected_i");}
    if (VL_UNLIKELY((vlSelfRef.aes_done_i & 0xfeU))) {
        Verilated::overWidthError("aes_done_i");}
}
#endif  // VL_DEBUG
