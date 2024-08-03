import numpy as np
import matplotlib.pyplot as plt
import sys
import math

# y = A sin(ωt + φ), ω = 2πf
def generate_signal(amplitude, frequency, phase, sampling_cnt):
    t = np.linspace(0, 1 / frequency, sampling_cnt, endpoint=False)
    signal = 0
    n_amplitude = amplitude
    for i in range(4):  
        signal = signal + n_amplitude * np.sin(2 * np.pi * frequency * (i + 1) * t + phase)
        n_amplitude = n_amplitude / 2 
    return t, signal

# Parameters for the signals
amplitude1 = 220*math.sqrt(2)
frequency = 50.0  # Frequency in Hz
phase1 = 0.0      # Phase in radians

amplitude2 = 4*math.sqrt(2)
phase2 = np.pi/6  # Phase in radians

# Signal duration and sampling rate
sampling_cnt = 128  # Sampling rate in samples per second

# Generate the signals
t1, signal1 = generate_signal(amplitude1, frequency, phase1, sampling_cnt)
t2, signal2 = generate_signal(amplitude2, frequency, phase2, sampling_cnt)

file_path = f'Analog_Sample_Data.txt'
U_int = list(map(int, (signal1 / 0.046875) + 2048))
I_int = list(map(int, (signal2 / 0.00390625) + 2048))
with open(file_path, 'w') as file:
    sys.stdout = file
    print(f'U_Sample:\n{U_int}')
    print(f'I_Sample:\n{I_int}')
    sys.stdout = sys.__stdout__

P = signal1 * signal2
P = np.round(P, 7)
Pu = sum(P) / sampling_cnt
print(f'有功功率：P={Pu}')
Vrms = np.sqrt(sum(signal1**2) / sampling_cnt)
Irms = np.sqrt(sum(signal2**2) / sampling_cnt)
apparent_power = Vrms * Irms
print(f'视在功率：P={apparent_power}')
print(f'功率因数：S={Pu / apparent_power}')
# Plot the signals
plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(t1, signal1, label=f'Frequency: {frequency} Hz, Phase: {phase1} rad')
plt.title('U')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(t2, signal2, label=f'Frequency: {frequency} Hz, Phase: {phase2} rad', color='orange')
plt.title('I')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.legend()

plt.tight_layout()
plt.show()

print(len(signal1))


