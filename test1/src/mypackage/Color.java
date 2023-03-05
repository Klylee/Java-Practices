package mypackage;

public class Color {
    private int red;
    private int green;
    private int blue;
    private float alpha;

    public Color() {
        this.red = 255;
        this.green = 255;
        this.blue = 255;
        this.alpha = 1;
    }

    public Color(int red, int green, int blue) {
        this.red = red;
        this.green = green;
        this.blue = blue;
        this.alpha = 1;
    }

    public Color(int red, int green, int blue, float alpha) {
        this.red = red;
        this.green = green;
        this.blue = blue;
        this.alpha = alpha;
    }

    public int red() {
        return this.red;
    }

    public int green() {
        return this.green;
    }

    public int blue() {
        return this.blue;
    }

    public float alpha() {
        return this.alpha;
    }
}
