public class Select implements Command {
  private boolean selected;
  
  private Entity selection;
  
  public void execute(String[] strs, World world) {
    if (strs.length == 3) {
      if (strs[1].equals("amazon")) {
        if (world.getAmazonMap().containsKey(strs[2])) {
          this.selection = world.getAmazonMap().get(strs[2]);
          this.selected = true;
          System.out.println(strs[2] + ", az amazon, kiválasztva.");
        } else if (world.getDinoszauruszMap().containsKey(strs[2])) {
          this.selection = world.getDinoszauruszMap().get(strs[2]);
          this.selected = true;
          System.out.println(strs[2] + ", a dinoszaurusz, kiválasztva.");
        } else {
          this.selected = false;
          System.out.println("ilyen névvel nincs amazon");
        } 
      } else if (strs[1].equals("dinoszaurusz")) {
        if (world.getDinoszauruszMap().containsKey(strs[2])) {
          this.selection = world.getDinoszauruszMap().get(strs[2]);
          this.selected = true;
          System.out.println(strs[2] + ", a dinoszaurusz, kiválasztva.");
        } else {
          this.selected = false;
          System.out.println("ilyen névvel nincs dinoszaurusz");
        } 
      } else {
        this.selected = false;
        System.out.println("ilyen típus nincs");
      } 
    } else if (strs.length > 3) {
      System.out.println("túl sok argumentum");
    } else {
      System.out.println("nincs elég argumentum");
    } 
  }
  
  public boolean execute() {
    return true;
  }
  
  public Entity getSelection() {
    return this.selection;
  }
  
  public boolean isSelected() {
    return this.selected;
  }
}
