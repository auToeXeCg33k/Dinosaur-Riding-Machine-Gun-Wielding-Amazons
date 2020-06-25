public class New implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 3) {
      if (strs[1].equals("amazon")) {
        if (world.getAmazonMap().containsKey(strs[2])) {
          System.out.println("ilyen amazon már van");
        } else {
          world.newAmazon(strs[2]);
          System.out.println(strs[2] + ", az amazon, létrehozva");
        } 
      } else if (strs[1].equals("dinoszaurusz")) {
        if (world.getDinoszauruszMap().containsKey(strs[2])) {
          System.out.println("ilyen dinoszaurusz már van");
        } else {
          world.newDinoszaurusz(strs[2]);
          System.out.println(strs[2] + ", a dinoszaurusz, létrehozva");
        } 
      } else {
        System.out.println("ilyen entitástípus nincs");
      } 
    } else if (strs.length > 3) {
      System.out.println("túl sok argumentum");
    } else {
      System.out.println("túl kevés argumentum");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
