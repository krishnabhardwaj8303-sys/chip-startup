* Arbiter PUF Cell -- Monte Carlo Delay Race (RC-line abstraction)
* Two RC lines (path A, path B) driven by the same input pulse model
* the two delay-buffer chains in arbiter_puf_cell.v. Each iteration
* randomizes R_A and R_B independently (uniform variation, +/-5% of
* nominal 1k ohm) as a proxy for SKY130 process-induced drive-strength
* mismatch between two nominally-identical buffer instances.
*
* SCOPE NOTE: simplified RC-delay-line Monte Carlo model (uniform
* variation), not a full transistor-level SKY130 standard-cell netlist
* with Gaussian process corners. Intended as a genuine, honestly-scoped
* first statistical signal on PUF uniqueness within a tight time
* budget. Full transistor-level SKY130 Gaussian Monte-Carlo is future work.

Vpulse pulse_in 0 PULSE(0 1.8 1n 10p 10p 20n 40n)

R1 pulse_in a 1k
C1 a 0 1p
R2 pulse_in b 1k
C2 b 0 1p

.control
set filetype=ascii

let n = 30
let wins_a = 0
let wins_b = 0
let ties = 0

let i = 0
while i < n
    let ra = 1000 + (rnd(101) - 50)
    let rb = 1000 + (rnd(101) - 50)
    alter R1 = $&ra
    alter R2 = $&rb

    tran 1p 10n

    meas tran ta WHEN v(a)=0.9 RISE=1
    meas tran tb WHEN v(b)=0.9 RISE=1

    if ta < tb
        let wins_a = wins_a + 1
        echo iteration $&i : Ra=$&ra Rb=$&rb -> A wins puf_bit=1
    else
        if tb < ta
            let wins_b = wins_b + 1
            echo iteration $&i : Ra=$&ra Rb=$&rb -> B wins puf_bit=0
        else
            let ties = ties + 1
            echo iteration $&i : TIE unstable
        end
    end

    let i = i + 1
end

echo ----------------------------------------
echo Monte Carlo summary over $&n iterations:
echo   A wins bit=1: $&wins_a
echo   B wins bit=0: $&wins_b
echo   ties unstable: $&ties
echo ----------------------------------------
.endc

.end
