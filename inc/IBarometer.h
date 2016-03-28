class IAltimeter {
    public: 
        virtual double getAltitude() = 0;
        virtual double getRawPressure() = 0;
        virtual void setAltitude(double alt) = 0;
}
