class OnePoleLpf {
public:
    double process(double input);
    void setCutoffFrequency(double cutoff_frequency);
    void setSampleRate(double sample_rate);
private:
    double previous_output_ = 0.0;
    double cutoff_frequency_ = 0.0;
    double sample_rate_ = 0.0;
    double alpha_ = 0.0; // calculated value based on cutoff frequency and sample rate
    void calculateAlpha();
};