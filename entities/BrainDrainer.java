package entities;

public class BrainDrainer {
    private final double minDMG;
    private final double maxDMG;


    public BrainDrainer() {
        this.minDMG = 60.0;
        this.maxDMG = 90.0;
    }
    
    public String attack (Amazon amazon) {
        java.util.Random random = new java.util.Random();
        double dmg = (maxDMG-minDMG)*random.nextDouble() + minDMG;
        String ret = amazon.getNev().concat(" amazont megbaszta a braindrainer. ");

        if (amazon.isLovagol()) {
            amazon.getDinoszaurusz().decHP(dmg);
            if (amazon.getDinoszaurusz().getHP() > 0.0)
                return ret.concat("A dinoszauruszának élete " + Math.round(dmg) + " ponttal csökkent. A megmaradt élete: " + Math.round(amazon.getDinoszaurusz().getHP()) + ".\n");

            amazon.setLovagol(false);
            return ret.concat(amazon.getNev().concat(" dinoszaurusza megdöglött.\n")) ;
        }

        amazon.decHP(dmg);
        if (amazon.getHP() != 0.0)
            return ret.concat("Az élete " + Math.round(dmg) + " ponttal csökkent. A megmaradt élete: " + Math.round(amazon.getHP()) + ".\n");

        return ret.concat("Meghótt a gecibe.\n");
    }
}
