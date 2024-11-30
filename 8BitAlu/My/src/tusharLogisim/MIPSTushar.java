package src.tusharLogisim;

import com.cburch.logisim.tools.AddTool;
import com.cburch.logisim.tools.Library;
import java.util.Arrays;
import java.util.List;

public class MIPSTushar extends Library {
   private List<AddTool> tools;

   public MIPSTushar() {
      this.tools = Arrays.asList(new AddTool(ALU8Bit.factory));
   }

   public String getDisplayName() {
      return "ALU:8_by_ART";
   }

   public List<AddTool> getTools() {
      return this.tools;
   }
}
