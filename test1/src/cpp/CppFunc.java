package cpp;

public class CppFunc {
    public native int initWindow(int width, int height, String name);

    public native int drawRectangle(int posx, int poxy, int width, int height, int r, int g, int b, float alpha);

    public native int drawCircular(int posx, int poxy, int radius, int r, int g, int b, float alpha);

    public native int drawTriangle(int posx, int poxy, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y,
            int r, int g, int b, float alpha);

    public native int drawBegin();
}
