package fft.maths;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;

public class Complex {

    private double real;
    private double imag;

    public Complex(double real, double imag) {

        this.real = real;
        this.imag = imag;
    }

    @NotNull
    public static ArrayList<Complex> fromScalars(@NotNull List<Double> scalars) {

        ArrayList<Complex> complexes = new ArrayList<>();

        scalars.forEach((scalar) -> complexes.add(new Complex(scalar, 0.0)));

        return complexes;
    }

    public Complex add(@NotNull Complex other) {
        return new Complex(this.real + other.real, this.imag + other.imag);
    }

    public Complex sub(@NotNull Complex other) {
        return new Complex(this.real - other.real, this.imag - other.imag);
    }

    public Complex mul(@NotNull Complex other) {
        return new Complex(this.real * other.real - this.imag * other.imag,
                this.real * other.imag + this.imag * other.real);
    }

    public double magnitude() {
        return Math.sqrt((this.real * this.real) + (this.imag * this.imag));
    }

    @SuppressWarnings("MethodDoesntCallSuperMethod")
    @Override
    public Complex clone() {
        return new Complex(this.real, this.imag);
    }

    @Override
    public String toString() {
        return String.format("(%f,%f)", this.real, this.imag);
    }
}
