public class Select implements Command {
  private Amazon selection;
  
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (world.getAmazonMap().containsKey(strs[1])) {
        this.selection = world.getAmazonMap().get(strs[1]);
        System.out.println(strs[1] + " kiválasztva.");
      } else {
        this.selection = null;
        System.out.println("ilyen névvel nincs amazon");
      } 
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return true;
  }
  
  public Amazon getSelection() {
    return this.selection;
  }
}
