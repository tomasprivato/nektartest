<?xml version="1.0" encoding="utf-8"?>
<test>
    <description>2D unsteady DG advection, quad, order 4, P=Variable</description>
    <executable>ADRSolver</executable>
    <parameters>Advection2D_m12_DG_quad_VarP.xml</parameters>
    <files>
        <file description="Session File">Advection2D_m12_DG_quad_VarP.xml</file>
    </files>
    <metrics>
        <metric type="L2" id="1">
            <value variable="u" tolerance="1e-9">3.83425e-06</value>
        </metric>
        <metric type="Linf" id="2">
            <value variable="u" tolerance="1e-9">8.09127e-05</value>
        </metric>
    </metrics>
</test>

