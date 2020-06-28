public class Drop implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (world.getItemClassMap().get(strs[1]) != null) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                Item temp = ((Select)world.getCommandMap().get("select")).getSelection().dropFromInventory(world.getItemClassMap().get(strs[1]));
                if (temp != null) {
                  world.getTiles()[i][j].addItem(temp);
                  System.out.println(strs[1] + "eldobva");
                  return;
                } 
                System.out.println("nem sikerült eldobni");
                return;
              } 
            } 
          } 
        } else {
          System.out.println("ilyen item nincs is");
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummenyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
