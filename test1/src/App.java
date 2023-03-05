import java.util.Vector;

import cpp.CppFunc;

import java.io.File;
import java.lang.ref.SoftReference;

import mypackage.*;
import cpp.*;

public class App {
    public static void main(String[] args) throws Exception {
        GraphType type = GraphType.CIRCULAR;
        File directory = new File("");
        String abspath = "F:/tempTasks/video/javaspace/test/test/resources/window.ui";
        System.out.println(abspath);
        UI ui = new UI(abspath);
        Vector<Graph> graphs = new Vector<>(0);
        SoftReference<Vector<Graph>> g = new SoftReference<Vector<Graph>>(graphs);
        ui.Parser(g);

        CppFunc cpp = new CppFunc();
        cpp.initWindow(500, 300, "graph window");
        for (var each : graphs) {
            if (each.getType() == GraphType.RECTANGLE) {
                Rectangle rect = (Rectangle) each;
                cpp.drawRectangle((int) rect.position().x(), (int) rect.position().y(), (int) rect.width(),
                        (int) rect.height(),
                        rect.color().red(), rect.color().green(), rect.color().blue(),
                        rect.color().alpha());
            } else if (each.getType() == GraphType.TRIANGLE) {
                Triangle tri = (Triangle) each;
                cpp.drawTriangle((int) tri.position().x(), (int) tri.position().y(), (int) tri.v1().x(),
                        (int) tri.v1().y(),
                        (int) tri.v2().x(), (int) tri.v2().y(), (int) tri.v3().x(), (int) tri.v3().y(),
                        tri.color().red(), tri.color().green(), tri.color().blue(),
                        tri.color().alpha());
            } else if (each.getType() == GraphType.CIRCULAR) {
                Circular cir = (Circular) each;
                cpp.drawCircular((int) cir.position().x(), (int) cir.position().y(),
                        cir.radius(),
                        cir.color().red(), cir.color().green(), cir.color().blue(),
                        cir.color().alpha());
            }
        }

        cpp.drawBegin();
    }

    static {
        String abspath = "F:/tempTasks/Dll1/x64/Debug/Dll1.dll";
        System.load(abspath);
    }
}
