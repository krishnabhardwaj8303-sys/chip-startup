// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vregister_map__pch.h"

//============================================================
// Constructors

Vregister_map::Vregister_map(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vregister_map__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , reg_write{vlSymsp->TOP.reg_write}
    , reg_read{vlSymsp->TOP.reg_read}
    , reg_addr{vlSymsp->TOP.reg_addr}
    , reg_ready{vlSymsp->TOP.reg_ready}
    , bist_pass_i{vlSymsp->TOP.bist_pass_i}
    , bist_fail_i{vlSymsp->TOP.bist_fail_i}
    , wdt_timeout_i{vlSymsp->TOP.wdt_timeout_i}
    , glitch_detected_i{vlSymsp->TOP.glitch_detected_i}
    , aes_done_i{vlSymsp->TOP.aes_done_i}
    , aes_start_o{vlSymsp->TOP.aes_start_o}
    , bist_start_o{vlSymsp->TOP.bist_start_o}
    , wdt_enable_o{vlSymsp->TOP.wdt_enable_o}
    , reg_wdata{vlSymsp->TOP.reg_wdata}
    , reg_rdata{vlSymsp->TOP.reg_rdata}
    , aes_result_i{vlSymsp->TOP.aes_result_i}
    , aes_key_o{vlSymsp->TOP.aes_key_o}
    , aes_plaintext_o{vlSymsp->TOP.aes_plaintext_o}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vregister_map::Vregister_map(const char* _vcname__)
    : Vregister_map(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vregister_map::~Vregister_map() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vregister_map___024root___eval_debug_assertions(Vregister_map___024root* vlSelf);
#endif  // VL_DEBUG
void Vregister_map___024root___eval_static(Vregister_map___024root* vlSelf);
void Vregister_map___024root___eval_initial(Vregister_map___024root* vlSelf);
void Vregister_map___024root___eval_settle(Vregister_map___024root* vlSelf);
void Vregister_map___024root___eval(Vregister_map___024root* vlSelf);

void Vregister_map::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vregister_map::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vregister_map___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vregister_map___024root___eval_static(&(vlSymsp->TOP));
        Vregister_map___024root___eval_initial(&(vlSymsp->TOP));
        Vregister_map___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vregister_map___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vregister_map::eventsPending() { return false; }

uint64_t Vregister_map::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vregister_map::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vregister_map___024root___eval_final(Vregister_map___024root* vlSelf);

VL_ATTR_COLD void Vregister_map::final() {
    Vregister_map___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vregister_map::hierName() const { return vlSymsp->name(); }
const char* Vregister_map::modelName() const { return "Vregister_map"; }
unsigned Vregister_map::threads() const { return 1; }
void Vregister_map::prepareClone() const { contextp()->prepareClone(); }
void Vregister_map::atClone() const {
    contextp()->threadPoolpOnClone();
}
