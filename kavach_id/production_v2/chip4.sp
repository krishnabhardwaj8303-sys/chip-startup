* Chip 4: Ra0=1005 Rb0=995
Vpulse pulse_in 0 PULSE(0 1.8 1n 10p 10p 20n 40n)
R1 pulse_in a 1k
C1 a 0 1p
R2 pulse_in b 1k
C2 b 0 1p

.control
set filetype=ascii

alter R1 = 1005
alter R2 = 995
tran 1p 10n
meas tran ta0 WHEN v(a)=0.9 RISE=1
meas tran tb0 WHEN v(b)=0.9 RISE=1
let true_bit = 0
if ta0 < tb0
    let true_bit = 1
end

let match_count = 0
let mismatch_count = 0

let idx = 0
while idx < 20
    let noise_a = (rnd(21) - 10)
    let noise_b = (rnd(21) - 10)
    let ra_n = 1005 + noise_a
    let rb_n = 995 + noise_b
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
        let match_count = match_count + 1
    else
        let mismatch_count = mismatch_count + 1
    end

    let idx = idx + 1
end

echo CHIP_4_RESULT Ra0=1005 Rb0=995 true_bit=$&true_bit matches=$&match_count mismatches=$&mismatch_count
.endc

.end
