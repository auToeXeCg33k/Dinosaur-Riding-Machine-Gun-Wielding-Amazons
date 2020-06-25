public class Where implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 3) {
      if (strs[1].equals("amazon")) {
        if (world.getAmazonMap().containsKey(strs[2])) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(world.getAmazonMap().get(strs[2])))
                System.out.println("Az amazon a(z) " + i + ";" + j + " koordinátán van"); 
            } 
          } 
        } else {
          System.out.println("ilyen amazon nincs");
        } 
      } else if (strs[1].equals("dinoszaurusz")) {
        if (world.getDinoszauruszMap().containsKey(strs[2])) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsDinoszaurusz(world.getDinoszauruszMap().get(strs[2])))
                System.out.println("A dinoszaurusz a(z) " + i + ";" + j + " koordinátán van"); 
            } 
          } 
        } else {
          System.out.println("ilyen dinoszaurusz nincs");
        } 
      } 
    } else if (strs.length < 3) {
      System.out.println("nincs elég argumentum");
    } else {
      System.out.println("túl sok argumentum");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
