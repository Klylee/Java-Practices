package mypackage;

public class Vec2d {
    private float x;
    private float y;

    public Vec2d() {
        this.x = 0;
        this.y = 0;
    }

    public Vec2d(Vec2d vec) {
        this.x = vec.x();
        this.y = vec.y();
    }

    public Vec2d(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Vec2d(int x, int y) {
        this.x = (float) x;
        this.y = (float) y;
    }

    public float x() {
        return this.x;
    }

    public float y() {
        return this.y;
    }

    public float mod() {
        return (float) Math.sqrt(x * x + y * y);
    }

    public void normalize() {
        float mod = mod();
        x = x / mod;
        y = y / mod;
    }
}
