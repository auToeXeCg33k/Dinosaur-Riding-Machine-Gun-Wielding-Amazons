public class Equip implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (world.getItemClassMap().get(strs[1]) != null) {
            if (((Select)world.getCommandMap().get("select")).getSelection().equip(world.getItemClassMap().get(strs[1]))) {
              System.out.println(strs[1] + " kézbe véve");
              return;
            } 
            System.out.println("nincs ilyen fegyver az inventoryban");
            return;
          } 
          System.out.println("ilyen fegyver nincs is");
          return;
        } 
        System.out.println("A kiválasztott amazon nem is él");
        return;
      } 
      System.out.println("válasszá ki valakit");
      return;
    } 
    System.out.println("nem megfelelő argumentummenyiség");
  }
  
  public boolean execute() {
    return false;
  }
}
