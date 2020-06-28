public class Tame implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (world.getDinoszauruszMap().containsKey(strs[1])) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection()))
                if (world.getTiles()[i][j].containsDinoszaurusz(world.getDinoszauruszMap().get(strs[1]))) {
                  ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getDinoszauruszMap().get(strs[1]));
                } else {
                  System.out.println("ez a dínó nincs a közelben");
                }  
            } 
          } 
        } else {
          System.out.println("ilyen dínó nincs is");
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentumszám");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
