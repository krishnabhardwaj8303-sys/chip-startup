* Arbiter PUF Cell -- Monte Carlo Uniqueness + Reliability (RC-line abstraction)
* PART 1 - UNIQUENESS: randomize R_A/R_B across N_UNIQ iterations (+/-5%)
* PART 2 - RELIABILITY: fix one chip, re-measure N_REL times with small noise (+/-1%)
* SCOPE NOTE: simplified RC-delay-line Monte Carlo, not full transistor-level SKY130.

Vpulse pulse_in 0 PULSE(0 1.8 1n 10p 10p 20n 40n)

R1 pulse_in a 1k
C1 a 0 1p
R2 pulse_in b 1k
C2 b 0 1p

.control
set filetype=ascii

let n_uniq = 500
let wins_a = 0
let wins_b = 0
let ties = 0

let i = 0
while i < n_uniq
    let ra = 1000 + (rnd(101) - 50)
    let rb = 1000 + (rnd(101) - 50)
    alter R1 = $&ra
    alter R2 = $&rb

    tran 1p 10n

    meas tran ta WHEN v(a)=0.9 RISE=1
    meas tran tb WHEN v(b)=0.9 RISE=1

    if ta < tb
        let wins_a = wins_a + 1
    else
        if tb < ta
            let wins_b = wins_b + 1
        else
            let ties = ties + 1
        end
    end

    let i = i + 1
end

echo ========================================
echo UNIQUENESS RESULT over $&n_uniq iterations:
echo   A wins bit=1: $&wins_a
echo   B wins bit=0: $&wins_b
echo   ties unstable: $&ties
echo ========================================

let ra0 = 1030
let rb0 = 970

let n_rel = 50
let rel_match = 0
let rel_mismatch = 0

alter R1 = $&ra0
alter R2 = $&rb0
tran 1p 10n
meas tran ta0 WHEN v(a)=0.9 RISE=1
meas tran tb0 WHEN v(b)=0.9 RISE=1
let true_bit = 0
if ta0 < tb0
    let true_bit = 1
end
echo Fixed chip Ra0=$&ra0 Rb0=$&rb0 -> true_bit=$&true_bit

let j = 0
while j < n_rel
    let noise_a = (rnd(21) - 10)
    let noise_b = (rnd(21) - 10)
    let ra_n = ra0 + noise_a
    let rb_n = rb0 + noise_b
    alter R1 = $&ra_n
    alter R2 = $&rb_n

    tran 1p 10n

    meas tran taj WHEN v(a)=0.9 RISE=1
    meas tran tbj WHEN v(b)=0.9 RISE=1

    let this_bit = 0
    if taj < tbj
        let this_bit = 1
    end

    if this_bit = true_bit
        let rel_match = rel_match + 1
    else
        let rel_mismatch = rel_mismatch + 1
    end

    let j = j + 1
end

echo ========================================
echo RELIABILITY RESULT over $&n_rel repeated measurements of one chip:
echo   matches true_bit: $&rel_match
echo   mismatches bit flips: $&rel_mismatch
echo ========================================
.endc

.end
