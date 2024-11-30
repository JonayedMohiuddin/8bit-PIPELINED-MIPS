package src.tusharLogisim;

import com.cburch.logisim.circuit.CircuitState;
import com.cburch.logisim.comp.AbstractComponentFactory;
import com.cburch.logisim.comp.Component;
import com.cburch.logisim.comp.ComponentDrawContext;
import com.cburch.logisim.comp.ComponentFactory;
import com.cburch.logisim.comp.ManagedComponent;
import com.cburch.logisim.data.AttributeSet;
import com.cburch.logisim.data.BitWidth;
import com.cburch.logisim.data.Bounds;
import com.cburch.logisim.data.Direction;
import com.cburch.logisim.data.Location;
import com.cburch.logisim.data.Value;
import com.cburch.logisim.util.GraphicsUtil;
import java.awt.Color;
import java.awt.Graphics;

public class ALU8Bit extends ManagedComponent {
   public static final ComponentFactory factory = new ALU8Bit.Factory();
   private static final BitWidth BITWIDTH_3 = BitWidth.create(3);
   private static final BitWidth BITWIDTH_8 = BitWidth.create(8);
   private static final BitWidth BITWIDTH_1 = BitWidth.create(1);

   public ALU8Bit(Location var1, AttributeSet var2) {
      super(var1, var2, 5);
      this.setEnd(0, var1.translate(-30, -30), BITWIDTH_8, 1);
      this.setEnd(1, var1.translate(-30, 30), BITWIDTH_8, 1);
      this.setEnd(2, var1.translate(-10, 40), BITWIDTH_3, 1);
      this.setEnd(3, var1.translate(30, -20), BITWIDTH_1, 2);
      this.setEnd(4, var1.translate(30, 0), BITWIDTH_8, 2);
      this.setEnd(5, var1.translate(30, 20), BITWIDTH_1, 2);
   }

   public ComponentFactory getFactory() {
      return factory;
   }

   public void propagate(CircuitState var1) {
      int var2 = var1.getValue(this.getEndLocation(0)).toIntValue();
      int var3 = var1.getValue(this.getEndLocation(1)).toIntValue();
      int var4 = var1.getValue(this.getEndLocation(2)).toIntValue();
      var2 = var2 << 24 >> 24;
      var3 = var3 << 24 >> 24;
      int var5 = 0;
      byte var6 = 0;
      byte var7 = 0;
      switch(var4) {
      case 0:
         var5 = var2 + var3;
         if (var2 + var3 < -128 || var2 + var3 > 127) {
            var6 = 1;
         }
         break;
      case 1:
         var5 = var2 - var3;
         if (var2 - var3 < -128 || var2 - var3 > 127) {
            var6 = 1;
         }
         break;
      case 2:
         var5 = var2 | var3;
         break;
      case 3:
         var5 = var2 & var3;
         break;
      case 4:
         var5 = ~(var2 | var3);
         break;
      case 5:
         var5 = var2 << var3;
         break;
      case 6:
         var5 = var2 >>> var3;
         if (var3 < 0) {
            short var8 = 255;
            int var11 = var8 >>> var2;
            var5 &= var11;
         }
         break;
      case 7:
         var5 = var3 >> var2;
      }

      if (var5 == 0) {
         var7 = 1;
      }

      Value var12 = Value.createKnown(BITWIDTH_8, var5);
      Value var9 = Value.createKnown(BITWIDTH_1, var7);
      Value var10 = Value.createKnown(BITWIDTH_1, var6);
      var1.setValue(this.getEndLocation(3), var9, this, 4);
      var1.setValue(this.getEndLocation(4), var12, this, 5);
      var1.setValue(this.getEndLocation(5), var10, this, 4);
   }

   static void drawALUIcon(ComponentDrawContext var0, int var1, int var2) {
      Graphics var3 = var0.getGraphics();
      var3.setColor(Color.BLACK);
      int[] var4 = new int[]{var1, var1 + 15, var1 + 15, var1, var1, var1 + 3, var1};
      int[] var5 = new int[]{var2, var2 + 5, var2 + 10, var2 + 15, var2 + 10, var2 + 8, var2 + 6};
      var3.drawPolygon(var4, var5, 7);
   }

   static void drawALU(Graphics var0, Bounds var1) {
      int var2 = var1.getWidth();
      int var3 = var1.getHeight();
      int var4 = var1.getX();
      int var5 = var4 + var2;
      int var6 = var1.getY();
      int var7 = var6 + var3;
      int[] var8 = new int[]{var4, var5, var5, var4, var4, var4 + 20, var4};
      int[] var9 = new int[]{var6, var6 + 30, var7 - 30, var7, var7 - 40, var7 - 50, var7 - 60};
      GraphicsUtil.switchToWidth(var0, 2);
      var0.drawPolygon(var8, var9, 7);
   }

   public void draw(ComponentDrawContext var1) {
      drawALU(var1.getGraphics(), this.getBounds());
      var1.drawPin(this, 0, "A", Direction.EAST);
      var1.drawPin(this, 1, "B", Direction.EAST);
      var1.drawPin(this, 3, "Zero", Direction.WEST);
      var1.drawPin(this, 4, "Res", Direction.WEST);
      var1.drawPin(this, 5, "OF ", Direction.WEST);
      var1.getGraphics().setColor(Color.GRAY);
      var1.drawPin(this, 2, "Op", Direction.SOUTH);
      var1.getGraphics().setColor(Color.BLACK);
   }

   private static class Factory extends AbstractComponentFactory {
      public String getName() {
         return "ALU-8 by ART";
      }

      public String getDisplayName() {
         return "ALU-8 by ART";
      }

      public Component createComponent(Location var1, AttributeSet var2) {
         return new ALU8Bit(var1, var2);
      }

      public Bounds getOffsetBounds(AttributeSet var1) {
         return Bounds.create(-30, -50, 60, 100);
      }

      public void paintIcon(ComponentDrawContext var1, int var2, int var3, AttributeSet var4) {
         ALU8Bit.drawALUIcon(var1, var2, var3);
      }
   }
}
