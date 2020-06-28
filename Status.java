public class Status implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " a neve.");
              System.out.println(((((Select)world.getCommandMap().get("select")).getSelection().getGepfegyver() != null) ? "Van" : "Nincs") + " fegyvere.");
              System.out.println(((((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) ? "Van" : "Nincs") + " dinoszaurusza.");
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().isLovagol() ? "Lovagol." : "Nem lovagol.");
              System.out.println("A(z) " + i + 1 + ";" + j + 1 + " koordinátán áll.");
            } 
          } 
        } 
      } else {
        System.out.println("válasszá valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummenyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
