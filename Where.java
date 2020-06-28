public class Where implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).isSelected()) {
        if (((Select)world.getCommandMap().get("select")).getSelection() instanceof Amazon) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection()))
                System.out.println(((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " a(z) " + ((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + ";" + i + 1 + " koordinátán van"); 
            } 
          } 
        } else {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsDinoszaurusz((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()))
                System.out.println(((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " a(z) " + ((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + ";" + i + 1 + " koordinátán van"); 
            } 
          } 
        } 
      } else {
        System.out.println("válasszá ki először vkit");
      } 
    } else {
      System.out.println("túl sok argumentum");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
