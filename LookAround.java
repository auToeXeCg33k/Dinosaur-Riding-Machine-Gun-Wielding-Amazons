import java.util.ArrayList;

public class LookAround implements Command {
  public void execute(String[] strs, World world) {
    System.out.println("WIP");
    if (strs.length == 1) {
      for (int i = 0; i < (world.getTiles()).length; i++) {
        for (int j = 0; j < (world.getTiles()[0]).length; j++) {
          if (world.getTiles()[i][j].containsAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection())) {
            ArrayList<Amazon> amazonArrayList = new ArrayList<>();
            ArrayList<Dinoszaurusz> dinoszauruszArrayList = new ArrayList<>();
            ArrayList arrayList = new ArrayList();
          } 
        } 
      } 
      System.out.println("A tartózkodási helyen az alábbiak találhatóak: ");
      System.out.println();
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
