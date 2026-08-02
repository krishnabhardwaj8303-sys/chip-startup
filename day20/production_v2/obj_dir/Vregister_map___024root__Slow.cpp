// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vregister_map.h for the primary calling header

#include "Vregister_map__pch.h"
#include "Vregister_map__Syms.h"
#include "Vregister_map___024root.h"

void Vregister_map___024root___ctor_var_reset(Vregister_map___024root* vlSelf);

Vregister_map___024root::Vregister_map___024root(Vregister_map__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vregister_map___024root___ctor_var_reset(this);
}

void Vregister_map___024root___configure_coverage(Vregister_map___024root* vlSelf, bool first);

void Vregister_map___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
    Vregister_map___024root___configure_coverage(this, first);
}

Vregister_map___024root::~Vregister_map___024root() {
}

// Coverage
void Vregister_map___024root::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    std::string fullhier = std::string{VerilatedModule::name()} + hierp;
    if (!fullhier.empty() && fullhier[0] == '.') fullhier = fullhier.substr(1);
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), VerilatedModule::name(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",fullhier,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}
