package tusharLogisim;

import com.cburch.logisim.circuit.CircuitState;
import com.cburch.logisim.comp.*;
import com.cburch.logisim.data.*;
import com.cburch.logisim.util.GraphicsUtil;
import java.awt.Graphics;
import java.awt.Color;

public class ALU4Bit extends ManagedComponent
{
    public static final ComponentFactory factory = new Factory();

    private static class Factory extends AbstractComponentFactory {
        private Factory() { }
        public String getName() { return "ALU 4-bit"; }
        public String getDisplayName() { return "ALU 4-bit (Tushar's Version)"; }
        public Component createComponent(Location loc, AttributeSet attrs) { return new ALU8Bit(loc, attrs); }
        public Bounds getOffsetBounds(AttributeSet attrs) { return Bounds.create(-30, -50, 60, 100); }
        public void paintIcon(ComponentDrawContext context, int x, int y, AttributeSet attrs) {
            drawALUIcon(context, x, y);
        }
    }

    public ALU4Bit(Location loc, AttributeSet attrs) {
        super(loc, attrs, 5);
        setEnd(0, loc.translate(-30, -30), BITWIDTH_4, 1);
        setEnd(1, loc.translate(-30, 30), BITWIDTH_4, 1);
        setEnd(2, loc.translate(-10, 40), BITWIDTH_3, 1);
        setEnd(3, loc.translate(30, -20), BITWIDTH_1, 2);
        setEnd(4, loc.translate(30, 0), BITWIDTH_4, 2);
        setEnd(5, loc.translate(30, 20), BITWIDTH_1, 2);
    }

    public ComponentFactory getFactory() { return factory; }

    public void propagate(CircuitState state) {
        int A = state.getValue(getEndLocation(0)).toIntValue();
        int B = state.getValue(getEndLocation(1)).toIntValue();
        int op = state.getValue(getEndLocation(2)).toIntValue();
        // get the right value from the sign-extension of '>>'
        A = (A << 28) >> 28;
        B = (B << 28) >> 28;
        int ans = 0;
        int overflow = 0;
        int zero = 0;
        switch(op)
        {
            case 0x0:
                // add
                ans = A + B;
                if(A+B < -8 || A+B > 7) {
                    overflow = 1;
                }
                break;

            case 0x1:
                // subtract
                ans = A - B;
                if(A-B < -8 || A-B > 7) {
                    overflow = 1;
                }
                break;

            case 0x2:
                // or
                ans = A | B;
                break;

            case 0x3:
                // and
                ans = A & B;
                break;

            case 0x4:
                // nor
                ans = ~(A | B);
                break;

            case 0x5:
                // sll
                // ans = B << A;
                ans = A >> B;
                break;

            case 0x6:
                // srl
                // ans = B >>> A;
                ans = A >>> B;
                break;

        }
        if(ans == 0) {
            zero = 1;
        }
        Value out = Value.createKnown(BITWIDTH_4, ans);
        Value outZero = Value.createKnown(BITWIDTH_1, zero);
        Value outOverflow = Value.createKnown(BITWIDTH_1, overflow);
        state.setValue(getEndLocation(3), outZero, this, 4);
        state.setValue(getEndLocation(4), out, this, 5);
        state.setValue(getEndLocation(5), outOverflow, this, 4);
    }

    static void drawALUIcon(ComponentDrawContext context, int x, int y) {
        Graphics g = context.getGraphics();
        g.setColor(Color.BLACK);
        int xp[] = {
                x, x+15, x+15, x   , x   , x+3, x
        };
        int yp[] = {
                y, y+5 , y+10, y+15, y+10, y+8, y+6
        };
        g.drawPolygon(xp, yp, 7);
    }

    static void drawALU(Graphics g, Bounds bds)
    {
        int wid = bds.getWidth();
        int ht = bds.getHeight();
        int x0 = bds.getX();
        int x1 = x0 + wid;
        int y0 = bds.getY();
        int y1 = y0 + ht;
        int xp[] = {
                x0, x1, x1, x0, x0, x0 + 20, x0
        };
        int yp[] = {
                y0, y0 + 30, y1 - 30, y1, y1 - 40, y1 - 50, y1 - 60
        };
        GraphicsUtil.switchToWidth(g, 2);
        g.drawPolygon(xp, yp, 7);
    }

    public void draw(ComponentDrawContext context)
    {
        drawALU(context.getGraphics(), getBounds());
        context.drawPin(this, 0, "A", Direction.EAST);
        context.drawPin(this, 1, "B", Direction.EAST);
        context.drawPin(this, 3, "Zero", Direction.WEST);
        context.drawPin(this, 4, "Res", Direction.WEST);
        context.drawPin(this, 5, "OF ", Direction.WEST);
        context.getGraphics().setColor(Color.GRAY);
        context.drawPin(this, 2, "Op", Direction.SOUTH);
        context.getGraphics().setColor(Color.BLACK);
    }

    private static final BitWidth BITWIDTH_4 = BitWidth.create(4);
    private static final BitWidth BITWIDTH_1 = BitWidth.create(1);
    private static final BitWidth BITWIDTH_3 = BitWidth.create(3);

}
