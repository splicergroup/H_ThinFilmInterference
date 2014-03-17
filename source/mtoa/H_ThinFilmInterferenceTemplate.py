import pymel.core as pm
import mtoa.utils as utils
import mtoa.ui.ae.utils as aeUtils
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate

class AEH_ThinFilmInterferenceTemplate(ShaderAETemplate):

    def setup(self):
        # Add the shader swatch to the AE
        self.addSwatch()
        self.beginScrollLayout()
 
        # Add a list that allows to replace the shader for other one
        self.addCustom('message', 'AEshaderTypeNew',
        'AEshaderTypeReplace')

        # Begins a "Color Section"
        self.beginLayout("TFI Controls", collapse=False)                                                      

        # Add a control for the "constatColor" shader attribute
        self.addControl("interference", label="Interference",
        annotation="Interference")

        self.addControl("ior_inside", label="Ior inside",
        annotation="Ior inside")

        self.addControl("ior_outside", label="Ior outside",
        annotation="Ior outside")

        self.addControl("min_thick", label="Min thickness",
        annotation="Min thickness")

        self.addControl("max_thick", label="Max thickness",
        annotation="Max thickness")

        self.addControl("multiplier", label="Multiplier",
        annotation="Multiplier")

        self.endLayout()

        # Begins a "Color Section"
        self.beginLayout("Sampling Controls", collapse=False)

        self.addControl("color_samples", label="Color samples",
        annotation="Color samples")

        self.endLayout()
 
        # include/call base class/node attributes
        pm.mel.AEdependNodeTemplate(self.nodeName)
 
        # Add Section for the extra controls not displayed before
        self.addExtraControls()
        self.endScrollLayout()