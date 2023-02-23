# DESCRIPTION

The signalGenerator creates a sinusoidal signal, and uses an external file (signal_msg) to publish the signal and the time. Then the signalProcessor subscribes to both, the signal and the time, and modifies the signal to create a new signal that is later plot.
