* Arbiter PUF Cell -- Reliability Test (fixed chip, repeated noisy measurement)
* Chip fixed at Ra0=1030, Rb0=970 (deterministic winner: B, since lower R
* charges faster -> smaller time constant -> crosses threshold first).
* true_bit = 0 (B wins) by RC circuit theory, confirmed analytically.
Vpulse pulse_in 0 PULSE(0 1.8 1n 10p 10p 20n 40n)

R1 pulse_in a 1k
C1 a 0 1p
R2 pulse_in b 1k
C2 b 0 1p

.control
set filetype=ascii

let n_rel_match = 0
let n_rel_mismatch = 0

let idx = 0
while idx < 50
    let noise_a = (rnd(21) - 10)
    let noise_b = (rnd(21) - 10)
    let ra_n = 1030 + noise_a
    let rb_n = 970 + noise_b
    alter R1 = $&ra_n
    alter R2 = $&rb_n

    tran 1p 10n

    meas tran taj WHEN v(a)=0.9 RISE=1
    meas tran tbj WHEN v(b)=0.9 RISE=1

    let this_bit = 0
    if taj < tbj
        let this_bit = 1
    end

    if this_bit = 0
        let n_rel_match = n_rel_match + 1
    else
        let n_rel_mismatch = n_rel_mismatch + 1
    end

    let idx = idx + 1
end

echo ========================================
echo RELIABILITY RESULT over 50 repeated measurements of one chip:
echo   Ra0=1030 Rb0=970 expected true_bit=0
echo   matches true_bit: $&n_rel_match
echo   mismatches bit flips: $&n_rel_mismatch
echo ========================================
.endc

.end
